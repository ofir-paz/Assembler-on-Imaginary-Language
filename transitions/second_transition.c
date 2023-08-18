/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * second_transition.c
 *
 * This file contains functions and logic for the second transition phase of an assembler.
 * During the second transition, the assembler processes the source code to generate the final
 * machine code by translating assembly instructions and data into binary representations.
 *
 * The functions in this file contribute to the final translation of the source code, focusing
 * on generating machine code, resolving symbols, and producing the binary output for each line.
 * This phase involves utilizing symbol tables and addressing methods to create the machine code.
 *
 * The second transition phase plays a crucial role in the completion of the assembly process.
 * It transforms the processed assembly lines into executable machine code that can be executed
 * on the target architecture.
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
#include "../errors/error_types/error_types.h"
#include "../errors/SecondTransitionErrors/SecondTransitionErrors.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

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
    char *extFileContents = NULL; /* Will hold the contents of the .ext file. */

    MemoryImage *memoryImage = createMemoryImage(
            *getCounterPointer(astList, IC_) - PROGRAM_MEM_START,
            *getCounterPointer(astList, DC_) - PROGRAM_MEM_START);

    /* Travers through the ASTs (not the file). */
    process_result secondTransitionRes =
            secondFileTraverse(file_name, astList, labelsMap, memoryImage, &extFileContents);

    if (secondTransitionRes == SUCCESS) /* If there were no errors, create the output files. */
        createOutputFiles(file_name, memoryImage, labelsMap[ENTRY], &extFileContents);

    clearMemoryImage(&memoryImage); /* Delete memory image. */

    return secondTransitionRes;
}

/*
 * Initiates the traversal and processing of the source file during the second transition phase.
 * Will traverse through the ASTs created in the first transition instead of the source file.
 *
 * @param   *file_name          The name of the source file being processed.
 * @param   *astList            Pointer to the list of abstract syntax trees.
 * @param   *labelsMap          Array of pointers to symbol tables for label management.
 * @param   *memoryImage        Pointer to the memory image structure for storing machine code.
 * @param   **extFileContents   Pointer to the string of external file contents for reference.
 *
 * @return  A process_result indicating the outcome of the second transition phase.
 */
process_result secondFileTraverse(const char *file_name, ast_list_t *astList,
                                  NameTable *labelsMap[], MemoryImage *memoryImage,
                                  char **extFileContents)
{
    ast_list_node_t *currAstNode = getAstHead(astList);
    int currLine = FIRST_LINE;
    boolean wasError = FALSE; /* Indicates if there was an error. */

    while (currAstNode != NULL) /* Traverse through the ASTs and handle them. */
    {
        ast_t *lineAst = getAst(currAstNode);

        handleLineInSecondTrans(file_name, currLine, lineAst, labelsMap, memoryImage,
                                extFileContents, &wasError);

        currAstNode = getNextAstNode(currAstNode); /* Go to next AST */
        currLine++; /* Increase line counter by 1 (each AST represents a different line). */
    }

    return (wasError == FALSE)? SUCCESS : FAILURE;
}

/*
 * Handles a line of assembly code during the second transition phase.
 *
 * @param   *file_name          The name of the source file being processed.
 * @param   currLine            The current line number in the source file.
 * @param   *lineAst            The abstract syntax tree (AST) representing the processed line.
 * @param   *labelsMap          An array of pointers to symbol tables for label management.
 * @param   *memoryImage        Pointer to the memory image structure for storing machine code.
 * @param   **extFileContents   Pointer to the string of external file contents.
 * @param   *wasError           Pointer to a boolean indicating if an error occurred.
 */
void handleLineInSecondTrans(const char *file_name, int currLine, ast_t *lineAst,
                             NameTable *labelsMap[], MemoryImage *memoryImage,
                             char **extFileContents, boolean *wasError)
{
    /* Update addresses of entry labels based on data from first transition. */
    Error lineError = updateTablesIfNeededInSecondTrans(lineAst,
                                                        labelsMap[NORMAL], labelsMap[ENTRY]);
    if (lineError == NO_ERROR)
        lineError = checkUndefinedLabelArgumentError(lineAst, labelsMap[NORMAL], labelsMap[EXTERN]);

    /* Handle found errors (if found). */
    handleLineErrorInSecondTrans(file_name, currLine, lineError, wasError);

    /* Encode instruction\data and add content (if needed) to ext file if there was no error. */
    if (*wasError == FALSE)
        encodeLine(lineAst, memoryImage, labelsMap[NORMAL], labelsMap[EXTERN], extFileContents);
}

/*
 * Updates symbol tables if needed during the second transition phase.
 *
 * @param   *lineAst       The abstract syntax tree (AST) representing the processed line.
 * @param   *normalLabels  The normal symbol table for label management.
 * @param   *entLabels     The entry symbol table for label management.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error updateTablesIfNeededInSecondTrans(ast_t *lineAst, NameTable *normalLabels,
                                        NameTable *entLabels)
{
    Error lineError = NO_ERROR;

    /* If need to update table. */
    if (getSentence(lineAst).sentenceType == GUIDANCE_SENTENCE &&
        getSentence(lineAst).sentence.guidance == ent)
    {
        arg_node_t *currEntLabel = getArgList(lineAst);

        /* Update all .entry arguments to the address of their definition in the file. */
        while (currEntLabel != NULL)
        {
            lineError = updateEntTable(normalLabels, entLabels, currEntLabel);
            currEntLabel = getNextNode(currEntLabel);
        }
    }

    return lineError;
}

/*
 * Updates the entry symbol table during the second transition phase.
 *
 * @param   *normalLabels    The normal symbol table for label management.
 * @param   *entLabels       The entry symbol table for label management.
 * @param   *entLabelArgNode The argument node containing the entry label information.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error updateEntTable(NameTable *normalLabels, NameTable *entLabels, arg_node_t *entLabelArgNode)
{
    char *entLabel = getArgData(entLabelArgNode).data.string; /* The name of the label. */

    Error lineError = checkEntryLabelError(entLabel, normalLabels); /* Check validation. */

    if (lineError == NO_ERROR)
        (void) setNumberInData(entLabels, entLabel,
                               getDataByName(normalLabels, entLabel) -> num);

    return lineError;
}

/*
 * Creates the output files containing the machine code (in the .ob file),
 * entry labels (in the .ent file), and external references (in the .ext file).
 * If there is no need to print the .ent or .ext file, will not print them.
 * The .ob file will always be printed.
 *
 * @param   *file_name          The name of the source file being processed.
 * @param   *memoryImage        A pointer to the memory image structure containing machine code.
 * @param   *entLabels          The entry symbol table for label management.
 * @param   **extFileContents   Pointer to the array of external file contents for reference.
 */
void createOutputFiles(const char *file_name, MemoryImage *memoryImage, NameTable *entLabels,
                       char **extFileContents)
{
    createObjectFile(file_name, memoryImage);
    createEntryFile(file_name, entLabels);
    createExternFile(file_name, extFileContents);
}

/*
 * Creates the object file (with ending .ob) containing the heading of the encoding,
 * After that the code segment (in Base64) and after that the data segment (also in Base64).
 *
 * @param   *file_name        The name of the source file being processed.
 * @param   *memoryImage      A pointer to the memory image structure containing machine code.
 */
void createObjectFile(const char *file_name, MemoryImage *memoryImage)
{
    /* Get the heading of the .ob file. */
    char *objectFileContents = getEncodingInformation(memoryImage);

    char *instructionSection = getEncodedWords(memoryImage, TRUE); /* Add the code segment. */
    char *dataSection = getEncodedWords(memoryImage, FALSE); /* Add the data segment. */

    /* Apply to string containing the header. */
    addTwoStrings(&objectFileContents, instructionSection);
    addTwoStrings(&objectFileContents, dataSection);

    writeToFile(file_name, OBJECT_END, objectFileContents);

    (void) clear_ptr(objectFileContents)
    (void) clear_ptr(instructionSection)
    (void) clear_ptr(dataSection)
}

/*
 * Creates the entry file containing the entry labels.
 *
 * @param   *file_name   The name of the source file being processed.
 * @param   *entTable    The entry symbol table containing entry label information.
 */
void createEntryFile(const char *file_name, NameTable *entTable)
{
    char *entryFileContents = numbersNameTableToString(entTable);

    writeToFile(file_name, ENT_END, entryFileContents);

    (void) clear_ptr(entryFileContents)
}

/*
 * Creates the extern file containing the external references.
 *
 * @param   *file_name          The name of the source file being processed.
 * @param   **extFileContents   Pointer string of external file contents for reference.
 */
void createExternFile(const char *file_name, char **extFileContents)
{
    /* The contents of the extern file was created in the encoding process. */
    writeToFile(file_name, EXT_END, *extFileContents);

    (void) clear_ptr(*extFileContents)
}