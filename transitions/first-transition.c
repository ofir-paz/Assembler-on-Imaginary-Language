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
#include "../errors/error_types/error_types.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/assemblerFinals.h"
#include "../FileHandling/readFromFile.h"
#include "../errors/errors.h"
#include "../util/memoryUtil.h"
#include "../encoding/encoding.h"
#include "first_transition_util.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
/* ------------ */

/* ---------------Prototypes--------------- */
process_result firstFileTraverse(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList);
ast_t *handleLineInFirstTrans(const char *file_name, const char *line, NameTable *labelsMap[],
                              int *IC, int *DC, boolean *wasError);
ast_t *firstAssemblerAlgo(const char *file_name, const char *line, int lineNumber,
                          NameTable *labelsMap[], int *IC, int *DC, boolean *wasError);
void addToTablesIfNeededInFirstTran(ast_t *lineAst, NameTable *labelsMap[], int IC,
                                    Error *lineError);
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
    int IC = ZERO_COUNT, DC = ZERO_COUNT;
    char *line = NULL; /* This will hold the current line */

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, AFTER_MACRO, &line) != EOF)
    {
        ast_t *lineAst = handleLineInFirstTrans(file_name, line, labelsMap, &IC, &DC, &wasError);
        if (wasError == FALSE) /* Add the ast to the list if there was no error. */
            (void) addAstToList(astList, &lineAst);
        (void) free_ptr(POINTER(line)); /* Next line */
    }

    (void) free_ptr(POINTER(line));
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
    addToTablesIfNeededInFirstTran(lineAst, labelsMap, *IC, &lineError);
    updateCounters(lineAst, IC, DC);

    *wasError = handleFirstTransLineError(file_name, lineNumber, lineError);
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
void addToTablesIfNeededInFirstTran(ast_t *lineAst, NameTable *labelsMap[], int IC,
                                    Error *lineError)
{
    label_type_t labelType = getLabelTypeForTable(lineAst);

    if (labelType != NO_LABEL_TYPE)
    {
        if (labelType == NORMAL && (*lineError = checkLabelDefTableError
                (lineAst, labelsMap[NORMAL], labelsMap[EXTERN])) == NO_ERROR)
            addLabelToTable(labelsMap[labelType],
                            getLabelName(lineAst), IC);

        else if (labelType == ENTRY)
            *lineError = addToEntryTable(lineAst, labelsMap);

        else /* labelType == EXTERN */
            *lineError = addToExternTable(lineAst, labelsMap);
    }
}

Error addToEntryTable(ast_t *lineAst, NameTable *labelsMap[])
{
    Error lineError;

    if (labelType == ENTRY)
        addToEn
}

Error addToExternTable(ast_t *lineAst, NameTable *labelsMap[])
{

}