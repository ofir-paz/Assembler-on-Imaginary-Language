/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include "../new-data-types/boolean.h"
#include "../new-data-types/process_result.h"
#include "../NameTable/NameTable.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/assemblerFinals.h"
#include "../encoding/encoding.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */

enum {OBJECT_CONTENT, ENTRY_CONTENT, EXTERN_CONTENT, CONTENT_AMOUNT};
/* ------------ */

/* ---------------Prototypes--------------- */
process_result secondFileTraverse(const char *file_name, ast_list_t *astList,
                                  NameTable *labelsMap[], MemoryImage *memoryImage,
                                  char **extFileContents);
void createOutputFiles(const char *file_name, char *outputFileContents[],
                       MemoryImage *memoryImage, NameTable *labelsMap[]);
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
    char *outputFileContents[CONTENT_AMOUNT] = {NULL};
    MemoryImage *memoryImage = createMemoryImage(
            *getCounterPointer(astList, IC_) - PROGRAM_MEM_START,
            *getCounterPointer(astList, DC_) - PROGRAM_MEM_START);

    process_result secondTransitionRes =
            secondFileTraverse(file_name, astList, labelsMap, memoryImage,
            outputFileContents + EXTERN_CONTENT);

    //if (secondTransitionRes == SUCCESS)
        //createOutputFiles(file_name, outputFileContents, memoryImage, labelsMap);

    //clearOutputFileContents(outputFileContents);
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
        ast_t *currAst = getAst(currNode);

        //handleSecondTransErrors(file_name, currLine, currAst,
        //                        labelsMap[NORMAL], labelsMap[ENTRY], &wasError);
        if (wasError == FALSE)
            encodeLine(currAst, memoryImage, labelsMap[NORMAL],
                       labelsMap[EXTERN], extFileContents);

        currNode = getNextAstNode(currNode);
        currLine++;
    }

    return (wasError == FALSE)? SUCCESS : FAILURE;
}

void createOutputFiles(const char *file_name, char *outputFileContents[],
                       MemoryImage *memoryImage, NameTable *labelsMap[])
{

}