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
#include "../encoding/assembler_ast.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/assemblerFinals.h"
#include "../FileHandling/readFromFile.h"
#include "../errors/FirstTransitionErrors/FirstTransitionErrors.h"
#include "../encoding/encoding.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
#include "first_transition_util.h"
/* -------------------------- */

/* ---Macros--- */

/* Will be used to distinguish between data labels and instruction labels. */
#define DATA_TEMP_ADDRESS(address) (-1 * (address))

/* ------------ */

/* ---Finals--- */
/* The address of the first instruction in the memory.
 * Cannot be zero, will produce errors if set to !! */
#define START_OF_PROGRAM_IN_MEM 100
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
/* ------------ */

/* ---------------Prototypes--------------- */
process_result firstFileTraverse(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList);
ast_t *handleLineInFirstTrans(const char *file_name, const char *line, NameTable *labelsMap[],
                              int *IC, int *DC, boolean *wasError);
ast_t *firstAssemblerAlgo(const char *file_name, const char *line, int lineNumber,
                          NameTable *labelsMap[], int *IC, int *DC, boolean *wasError);
void addToTablesIfNeededInFirstTrans(ast_t *lineAst, NameTable *labelsMap[], int IC, int DC,
                                    Error *lineError);
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

    return firstFileTraverse(file_name, labelsMap, *astList);
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
    int IC = START_OF_PROGRAM_IN_MEM, DC = START_OF_PROGRAM_IN_MEM;
    char *line = NULL; /* This will hold the current line */

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, AFTER_MACRO, &line) != EOF)
    {
        ast_t *lineAst = handleLineInFirstTrans(file_name, line, labelsMap, &IC, &DC, &wasError);
        if (wasError == FALSE) /* Add the ast to the list if there was no error. */
            (void) addAstToList(astList, &lineAst);
        (void) free_ptr(POINTER(line)); /* Next line */
    }
    (void) free_ptr(POINTER(line)); /* Free the last line. */

    if (wasError == FALSE)
        /* Separate instructions and data */
        updateDataLabels(labelsMap[NORMAL], IC - START_OF_PROGRAM_IN_MEM);

    return (wasError == FALSE)? SUCCESS : FAILURE;
}

/*
 * Handles the given line string in the pre-process.
 *
 * @param   *line Current line string.
 * @param   **macro_name Pointer to the current macro name.
 * @param   *amFile Data structure to hold the file to print.
 * @param   *macro_table Data structure to hold the macro names and contents.
 */
ast_t *handleLineInFirstTrans(const char *file_name, const char *line, NameTable *labelsMap[],
                              int *IC, int *DC, boolean *wasError)
{
    static int lineCount = ZERO_COUNT; /* Counter of line */
    lineCount++;

    return firstAssemblerAlgo(file_name, line, lineCount, labelsMap, IC, DC, wasError);
}

ast_t *firstAssemblerAlgo(const char *file_name, const char *line, int lineNumber,
                          NameTable *labelsMap[], int *IC, int *DC, boolean *wasError)
{
    Error lineError; /* Represents the error in the line (if there is). */

    /* AST (abstract syntax tree) representing the line to return. */
    ast_t *lineAst = buildAstFromLine(line, &lineError);
    lineError = handle_FirstTransLine_Error(file_name, lineNumber, lineAst, lineError);

    addToTablesIfNeededInFirstTrans(lineAst, labelsMap, *IC, *DC, &lineError);

    if (lineError == NO_ERROR)
        updateCounters(lineAst, IC, DC);
    else
        *wasError = TRUE;

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
void addToTablesIfNeededInFirstTrans(ast_t *lineAst, NameTable *labelsMap[], int IC, int DC,
                                      Error *lineError)
{
    label_type_t labelType = getLabelTypeForTable(lineAst);

    if (labelType == NORMAL)
            *lineError = addToNormalTable(lineAst, labelsMap[NORMAL],
                                          labelsMap[EXTERN], IC, DC);
    else if (labelType == ENTRY || labelType == EXTERN)
            *lineError = addToOtherTable(lineAst, labelsMap, labelType);
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
        addLabelToOtherTable(my_strdup(getArgData(currArg).data.string),
                             labelsMap, table, &lineError);
        currArg = getNextNode(currArg);
    }

    return lineError;
}