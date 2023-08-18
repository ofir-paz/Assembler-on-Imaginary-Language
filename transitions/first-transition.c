/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * first_transition.c
 *
 * This file contains functions and logic for the first transition phase of an assembler.
 * During the first transition, the assembler processes the source code to build symbol tables
 * and identify any errors that may affect further processing.
 *
 * The functions in this file contribute to the preliminary analysis of the source code,
 * focusing on preparing data structures for subsequent phases. This includes identifying labels,
 * and performing syntax checks that set the stage for further processing.
 *
 * As the first step in the assembly process, this phase plays a critical role in setting up the
 * groundwork for subsequent phases. The code in this file aims to ensure that the source code is
 * ready for further analysis, translation, and machine code generation.
 */

/* ---Include header files--- */
#include <stdio.h>
#include <string.h>
#include "../NameTable/NameTable.h"
#include "../new-data-types/process_result.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/assemblerFinals.h"
#include "../FileHandling/readFromFile.h"
#include "../errors/error_types/error_types.h"
#include "../errors/FirstTransitionErrors/FirstTransitionLogicalAndImgSystemErrors.h"
#include "../errors/assembler_errors.h"
#include "../errors/warnings.h"
#include "../util/memoryUtil.h"
#include "first_transition_util.h"
/* -------------------------- */

/* ---Finals--- */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
#define NO_LINE 0
/* ------------ */

/* ---Macros--- */

/* Will be used to distinguish between data labels and instruction labels. */
#define DATA_TEMP_ADDRESS(address) (-1 * (address))

/* ------------ */

/* ---------------Prototypes--------------- */
process_result firstFileTraverse(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList);
boolean handleLineInFirstTrans(const char *file_name, const char *line, int lineNumber,
                               ast_list_t *astList, NameTable *labelsMap[], int *IC, int *DC);
ast_t *firstAssemblerAlgo(const char *file_name, const char *line, int lineNumber,
                          NameTable *labelsMap[], int *IC, int *DC);
Error addToTablesIfNeededInFirstTrans(ast_t *lineAst, NameTable *labelsMap[], int IC, int DC);
Error addToNormalTable(ast_t *lineAst, NameTable *normalTable, NameTable *extTable, int IC, int DC);
Error addToOtherTable(ast_t *lineAst, NameTable *labelsMap[], label_type_t table);
/* ---------------------------------------- */

/*
 * Performs the first transition phase of an assembler on the given source file.
 *
 * @param   *file_name  The name of the source file to be processed.
 * @param   *labelsMap  An array of pointers to symbol tables for label management.
 * @param   **astList   A pointer to the list of abstract syntax trees for line processing.
 *
 * @return  A process_result indicating the outcome of the first transition phase.
 */
process_result first_transition(const char *file_name, NameTable *labelsMap[],
                                ast_list_t **astList)
{
    labelsMap[NORMAL] = createNameTable(INT_TYPE); /* Will hold normal labels */
    labelsMap[ENTRY] = createNameTable(INT_TYPE); /* Will hold the .entry labels. */
    labelsMap[EXTERN] = createNameTable(INT_TYPE); /* Will hold the .extern labels. */
    *astList = createAstList(); /* Data structure to help diagnose and encode each line. */

    process_result firstTransRes = firstFileTraverse(file_name, labelsMap, *astList);

    /* Check if the program is too big (memory overflow). */
    ImgSystemError imgSystemError = checkFileMemoryOverflow(*astList);

    if (imgSystemError != NO_ERROR) {
        handle_assembler_error(file_name, NO_LINE, imgSystemError);
        firstTransRes = FAILURE;
    }

    return firstTransRes;
}

/*
 * Initiates the traversal and processing of the source file during the first transition phase.
 *
 * @param   *file_name      The name of the source file to be processed.
 * @param   *labelsMap[]    An array of symbol tables for label management.
 * @param   *astList        A pointer to the list of abstract syntax trees for line processing.
 *
 * @return  A process_result indicating the outcome of the first transition phase.
 */
process_result firstFileTraverse(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList)
{
    boolean wasError = FALSE;
    int *IC = getCounterPointer(astList, IC_), *DC = getCounterPointer(astList, DC_);
    char *line = NULL; /* This will hold the current line */
    int readCode; /* Will hold the current line's read code. */
    int lineCount = ZERO_COUNT;

    *IC = *DC = PROGRAM_MEM_START; /* Initializing IC and DC. */
    /* Read the file line-by-line and handle it. */
    while ((readCode = readNextLineFromFile(file_name, AFTER_MACRO, &line)) != EOF)
    {
        if (readCode == UNABLE_TO_OPEN_FILE) break;

        lineCount++;
        boolean wasErrorInLine = handleLineInFirstTrans(file_name, line, lineCount,
                                                        astList, labelsMap, IC, DC);
        (void) clear_ptr(line) /* Next line */

        if (wasErrorInLine == TRUE) wasError = TRUE;
    }
    (void) clear_ptr(line) /* Free the last line. */

    /* Separate instructions and data */
    updateDataLabels(labelsMap[NORMAL], *IC - PROGRAM_MEM_START);

    return (wasError == FALSE && readCode != UNABLE_TO_OPEN_FILE)? SUCCESS : FAILURE;
}

/*
 * Handles a line of assembly code during the first transition phase.
 *
 * @param   *file_name    The name of the source file being processed.
 * @param   *line         The input line of assembly code.
 * @param   lineNumber    The line number in the source file.
 * @param   *astList      A pointer to the list of abstract syntax trees for line processing
 *                        (The created AST from the line will be added to the list).
 * @param   *labelsMap    An array of symbol tables for label management.
 * @param   *IC           A pointer to the Instruction Counter.
 * @param   *DC           A pointer to the Data Counter.
 *
 * @return  TRUE if the line is successfully handled, otherwise FALSE.
 */
boolean handleLineInFirstTrans(const char *file_name, const char *line, int lineNumber,
                               ast_list_t *astList, NameTable *labelsMap[], int *IC, int *DC)
{
    ast_t *lineAst = firstAssemblerAlgo(file_name, line, lineNumber, labelsMap, IC, DC);
    (void) addAstToList(astList, &lineAst); /* Add the ast to the list. */

    return (lineAst == NULL)? TRUE : FALSE;
}

/*
 * Initiates the first transition algorithm for processing an assembly file.
 *
 * @param   *file_name    The name of the source file being processed.
 * @param   *line         The input line of assembly code.
 * @param   lineNumber    The line number in the source file.
 * @param   *labelsMap    An array of symbol tables for label management.
 * @param   *IC           A pointer to the Instruction Counter.
 * @param   *DC           A pointer to the Data Counter.
 *
 * @return  The abstract syntax tree (AST) representing the processed line,
 *          or NULL if there was an error during processing.
 */
ast_t *firstAssemblerAlgo(const char *file_name, const char *line, int lineNumber,
                          NameTable *labelsMap[], int *IC, int *DC)
{
    Error lineError; /* Represents the error in the line (if there is). */

    /* AST (abstract syntax tree) representing the line to return. */
    ast_t *lineAst = buildAstFromLine(line, &lineError);

    if (lineAst != NULL) /* If the tree was built (there were no errors in the line itself) */
    {
        handleWarnings(file_name, lineNumber, lineAst); /* Handle warnings. */
        lineError = addToTablesIfNeededInFirstTrans(lineAst, labelsMap, *IC, *DC);
    }

    if (lineError != NO_ERROR) /* If there was an error. */
    {
        handle_assembler_error(file_name, lineNumber, lineError);
        deleteAst(&lineAst);
    }
    else /* Update the counters if there were no errors. */
        updateCounters(lineAst, IC, DC);


    return lineAst;
}

/*
 * Adds relevant entries to symbol tables if needed during the first transition phase.
 *
 * @param   *lineAst     The abstract syntax tree (AST) representing the processed line.
 * @param   *labelsMap   An array of symbol tables for label management.
 * @param   IC           The Instruction Counter value.
 * @param   DC           The Data Counter value.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addToTablesIfNeededInFirstTrans(ast_t *lineAst, NameTable *labelsMap[], int IC, int DC)
{
    Error lineError = NO_ERROR; /* Value to return. */

    label_type_t labelType = getLabelTypeForTable(lineAst);

    if (labelType == NORMAL)
            lineError = addToNormalTable(lineAst, labelsMap[NORMAL],
                                          labelsMap[EXTERN], IC, DC);
    else if (labelType == ENTRY || labelType == EXTERN)
            lineError = addToOtherTable(lineAst, labelsMap, labelType);

    return lineError;
}

/*
 * Adds an entry to the normal symbol table if needed during the first transition phase.
 *
 * @param   *lineAst      The abstract syntax tree (AST) representing the processed line.
 * @param   *normalTable  The normal symbol table for label management.
 * @param   *extTable     The external symbol table for reference management.
 * @param   IC            The Instruction Counter value.
 * @param   DC            The Data Counter value.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addToNormalTable(ast_t *lineAst, NameTable *normalTable, NameTable *extTable, int IC, int DC)
{
    Error lineError = checkLabelDefTableError(lineAst, normalTable, extTable);

    if (lineError == NO_ERROR)
    {
        /* The address will be decided based on the type of sentence. */
        int address = (getSentence(lineAst).sentenceType == DIRECTION_SENTENCE)?
                IC : DATA_TEMP_ADDRESS(DC);
        addLabelToTable(normalTable, getLabelName(lineAst), address);
    }

    return lineError;
}

/*
 * Adds an entry to the specified symbol table if needed during the first transition phase.
 *
 * @param   *lineAst     The abstract syntax tree (AST) representing the processed line.
 * @param   *labelsMap   An array of pointers to symbol tables for label management.
 * @param   table        The type of symbol table to add the entry to (NORMAL or EXTERN).
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addToOtherTable(ast_t *lineAst, NameTable *labelsMap[], label_type_t table)
{
    Error lineError = NO_ERROR; /* Value to return, assume no error. */

    /* Add all arguments of .entry or .extern guidance to the specific table. */
    arg_node_t *currArg = getArgList(lineAst);
    while (currArg != NULL)
    {
        addLabelToOtherTable(getArgData(currArg).data.string, labelsMap, table, &lineError);

        currArg = getNextNode(currArg);
    }

    return lineError;
}