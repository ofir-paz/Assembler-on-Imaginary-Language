/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../FileHandling/writeToFile.h"
#include "../new-data-types/process_result.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/assemblerFinals.h"
#include "../encoding/encoding.h"
#include "../errors/SecondTransitionErrors/SecondTransitionErrors.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

#include "../errors/error_types/error_types.h"

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define OBJECT_END ".ob"
#define ENT_END ".ent"
#define EXT_END ".ext"
/* ------------ */

/* ---------------Prototypes--------------- */
process_result secondFileTraverse(const char *file_name, ast_list_t *astList,
                                  NameTable *labelsMap[], MemoryImage *memoryImage,
                                  char **extFileContents);
void handleLineInSecondTrans(const char *file_name, int currLine, ast_t *lineAst,
                             NameTable *labelsMap[], MemoryImage *memoryImage,
                             char **extFileContents, boolean *wasError);
Error updateTablesIfNeededInSecondTrans(ast_t *lineAst, NameTable *normalLabels,
                                        NameTable *entLabels);
Error updateEntTable(NameTable *normalLabels, NameTable *entLabels, arg_node_t *entLabelArgNode);
void createOutputFiles(const char *file_name, MemoryImage *memoryImage, NameTable *entLabels,
                       char **extFileContents);
void createObjectFile(const char *file_name, MemoryImage *memoryImage);
void createEntryFile(const char *file_name, NameTable *entTable);
void createExternFile(const char *file_name, char **extFileContents);
/* ---------------------------------------- */

/*
 * Main method of second transition stage. will process the created list of
 * ASTs and produce the final product of the assembler.
 *
 * @param   *file_name      The name of the with the assembly source code.
 * @param   *labelsMap[]    Array of tables to hold the different labels.
 * @param   *astList        List of ASTs (Abstract syntax trees) that were made in the
 *                          first transition.
 * @param   *memoryImage    The memory image of the assembly code.
 *
 * @return  SUCCESS on success, FAILURE on failure.
 */
process_result second_transition(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList)
{
    char *extFileContents = NULL;
    MemoryImage *memoryImage = createMemoryImage(
            *getCounterPointer(astList, IC_) - PROGRAM_MEM_START,
            *getCounterPointer(astList, DC_) - PROGRAM_MEM_START);

    process_result secondTransitionRes =
            secondFileTraverse(file_name, astList, labelsMap, memoryImage, &extFileContents);

    if (secondTransitionRes == SUCCESS)
        createOutputFiles(file_name, memoryImage, labelsMap[ENTRY], &extFileContents);

    clearMemoryImage(&memoryImage);

    return secondTransitionRes;
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
process_result secondFileTraverse(const char *file_name, ast_list_t *astList,
                                  NameTable *labelsMap[], MemoryImage *memoryImage,
                                  char **extFileContents)
{
    ast_list_node_t *currNode = getAstHead(astList);
    int currLine = FIRST_LINE;
    boolean wasError = FALSE; /* Indicates if there was an error. */

    while (currNode != NULL)
    {
        ast_t *lineAst = getAst(currNode);

        handleLineInSecondTrans(file_name, currLine, lineAst, labelsMap, memoryImage,
                                extFileContents, &wasError);

        currNode = getNextAstNode(currNode);
        currLine++;
    }

    return (wasError == FALSE)? SUCCESS : FAILURE;
}

void handleLineInSecondTrans(const char *file_name, int currLine, ast_t *lineAst,
                             NameTable *labelsMap[], MemoryImage *memoryImage,
                             char **extFileContents, boolean *wasError)
{
    Error lineError = updateTablesIfNeededInSecondTrans(lineAst,
                                                        labelsMap[NORMAL], labelsMap[ENTRY]);
    if (lineError == NO_ERROR)
        lineError = checkUndefinedLabelArgumentError(lineAst, labelsMap[NORMAL], labelsMap[EXTERN]);

    handleLineErrorInSecondTrans(file_name, currLine, lineError, wasError);

    if (*wasError == FALSE)
        encodeLine(lineAst, memoryImage, labelsMap[NORMAL], labelsMap[EXTERN], extFileContents);
}

Error updateTablesIfNeededInSecondTrans(ast_t *lineAst, NameTable *normalLabels,
                                        NameTable *entLabels)
{
    Error lineError = NO_ERROR;

    /* If need to update table. */
    if (getSentence(lineAst).sentenceType == GUIDANCE_SENTENCE &&
        getSentence(lineAst).sentence.guidance == ent)
    {
        arg_node_t *currEntLabel = getArgList(lineAst);

        while (currEntLabel != NULL)
        {
            lineError = updateEntTable(normalLabels, entLabels, currEntLabel);
            currEntLabel = getNextNode(currEntLabel);
        }
    }

    return lineError;
}

Error updateEntTable(NameTable *normalLabels, NameTable *entLabels, arg_node_t *entLabelArgNode)
{
    char *entLabel = getArgData(entLabelArgNode).data.string;

    Error lineError = checkEntryLabelError(entLabel, normalLabels);

    if (lineError == NO_ERROR)
        (void) setNumberInData(entLabels, entLabel,
                               getDataByName(normalLabels, entLabel) -> num);

    return lineError;
}

void createOutputFiles(const char *file_name, MemoryImage *memoryImage, NameTable *entLabels,
                       char **extFileContents)
{
    createObjectFile(file_name, memoryImage);
    createEntryFile(file_name, entLabels);
    createExternFile(file_name, extFileContents);
}

void createObjectFile(const char *file_name, MemoryImage *memoryImage)
{
    char *objectFileContents = getEncodingInformation(memoryImage);

    char *instructionSection = getEncodedWords(memoryImage, TRUE);
    char *dataSection = getEncodedWords(memoryImage, FALSE);

    addTwoStrings(&objectFileContents, instructionSection);
    addTwoStrings(&objectFileContents, dataSection);

    writeToFile(file_name, OBJECT_END, objectFileContents);

    (void) clear_ptr(objectFileContents)
    (void) clear_ptr(instructionSection)
    (void) clear_ptr(dataSection)
}

void createEntryFile(const char *file_name, NameTable *entTable)
{
    char *entryFileContents = numbersNameTableToString(entTable);

    writeToFile(file_name, ENT_END, entryFileContents);

    (void) clear_ptr(entryFileContents)
}

void createExternFile(const char *file_name, char **extFileContents)
{
    writeToFile(file_name, EXT_END, *extFileContents);

    (void) clear_ptr(*extFileContents)
}