/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
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
#include "../util/stringsUtil.h"
#include "first_transition_util.h"
/* -------------------------- */

/* ---Macros--- */

/* Will be used to distinguish between data labels and instruction labels. */
#define DATA_TEMP_ADDRESS(address) (-1 * (address))

/* ------------ */

/* ---Finals--- */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
#define NO_LINE 0
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
 * Main method of first transition stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return
 */
process_result first_transition(const char *file_name, NameTable *labelsMap[],
                                ast_list_t **astList)
{
    labelsMap[NORMAL] = createNameTable(INT_TYPE); /* Will hold normal labels */
    labelsMap[ENTRY] = createNameTable(INT_TYPE); /* Will hold the .entry labels. */
    labelsMap[EXTERN] = createNameTable(INT_TYPE); /* Will hold the .extern labels. */
    *astList = createAstList(); /* Data structure to help diagnose and encode each line. */

    process_result firstTransRes = firstFileTraverse(file_name, labelsMap, *astList);
    ImgSystemError imgSystemError = checkFileMemoryOverflow(*astList);

    if (imgSystemError != NO_ERROR){
        handle_assembler_error(file_name, NO_LINE, imgSystemError);
        firstTransRes = FAILURE;
    }

    return firstTransRes;
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
process_result firstFileTraverse(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList)
{
    boolean wasError = FALSE;
    int *IC = getCounterPointer(astList, IC_), *DC = getCounterPointer(astList, DC_);
    char *line = NULL; /* This will hold the current line */
    ssize_t readCode; /* Will hold the current line's read code. */
    int lineCount = ZERO_COUNT;

    *IC = *DC = PROGRAM_MEM_START;
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
 * Handles the given line string in the pre-process.
 *
 * @param   *line Current line string.
 * @param   **macro_name Pointer to the current macro name.
 * @param   *amFile Data structure to hold the file to print.
 * @param   *macro_table Data structure to hold the macro names and contents.
 */
boolean handleLineInFirstTrans(const char *file_name, const char *line, int lineNumber,
                               ast_list_t *astList, NameTable *labelsMap[], int *IC, int *DC)
{
    ast_t *lineAst = firstAssemblerAlgo(file_name, line, lineNumber, labelsMap, IC, DC);
    (void) addAstToList(astList, &lineAst); /* Add the ast to the list. */

    return (lineAst == NULL)? TRUE : FALSE;
}

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

    if (lineError != NO_ERROR)
    {
        handle_assembler_error(file_name, lineNumber, lineError);
        deleteAst(&lineAst);
    }
    else
        updateCounters(lineAst, IC, DC);


    return lineAst;
}

/*
 * Adds content to the data structure if needed.
 * Will know if any addition is needed based on the given flags and line string.
 *
 * @param   *line The line string which the program is currently processing.
 * @param   *macro_name The macro name which is the program is currently working with.
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
Error addToTablesIfNeededInFirstTrans(ast_t *lineAst, NameTable *labelsMap[], int IC, int DC)
{
    Error lineError = NO_ERROR;

    label_type_t labelType = getLabelTypeForTable(lineAst);

    if (labelType == NORMAL)
            lineError = addToNormalTable(lineAst, labelsMap[NORMAL],
                                          labelsMap[EXTERN], IC, DC);
    else if (labelType == ENTRY || labelType == EXTERN)
            lineError = addToOtherTable(lineAst, labelsMap, labelType);

    return lineError;
}

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

Error addToOtherTable(ast_t *lineAst, NameTable *labelsMap[], label_type_t table)
{
    Error lineError = NO_ERROR; /* Value to return, assume no error. */

    arg_node_t *currArg = getArgList(lineAst);
    while (currArg != NULL)
    {
        addLabelToOtherTable(getArgData(currArg).data.string, labelsMap, table, &lineError);

        currArg = getNextNode(currArg);
    }

    return lineError;
}