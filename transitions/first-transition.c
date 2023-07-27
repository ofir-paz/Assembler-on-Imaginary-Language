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
#include "../errors/error_types/error_types.h"
#include "../general-enums/programEnums.h"
#include "TransitionNumber.h"
#include "../FileHandling/readFromFile.h"
#include "../errors/errors.h"
#include "../general_help_methods.h"
#include "../encoding/encoding.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
/* ------------ */

/* ---------------Prototypes--------------- */
process_result firstFileTraverse(const char *file_name,
                                 NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                                 MemoryImage *memoryImage);
Error handleLineInFirstTrans(const char *file_name, const char *line,
                 NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                 MemoryImage *memoryImage, int *IC, int *DC, boolean *wasError);
void firstAssemblerAlgo(const char *line,
                        NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                        MemoryImage *memoryImage, int *IC, int *DC);
void addToTablesIfNeededInFirstTran(const char *line,
                         NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                         int *IC, int *DC);
/* ---------------------------------------- */

/*
 * Main method of first transition stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return
 */
process_result first_transition(const char *file_name,
                                NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                                MemoryImage *memoryImage)
{
    regLabels = createNameTable(INT_TYPE); /* Will hold normal labels */
    entLabels = createNameTable(INT_TYPE); /* Will hold the .entry labels. */
    extLabels = createNameTable(INT_TYPE); /* Will hold the .extern labels. */

    return firstFileTraverse(file_name, regLabels, entLabels, extLabels, memoryImage);
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
process_result firstFileTraverse(const char *file_name,
                                 NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                                 MemoryImage *memoryImage)
{
    boolean wasError = FALSE;
    int IC, DC;
    char *line = NULL; /* This will hold the current line */

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, AFTER_MACRO, &line) != EOF)
    {
        (void) handleLineInFirstTrans(file_name, line, regLabels, entLabels, extLabels,
                                      memoryImage, &IC, &DC, &wasError);

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
Error handleLineInFirstTrans(const char *file_name, const char *line,
                 NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                 MemoryImage *memoryImage, int *IC, int *DC, boolean *wasError)
{
    static int lineCount = ZERO_COUNT; /* Counter of line */
    lineCount++;
    /* Value to return. Represents the error in the line (if there is). */
    Error lineError = handleLineErrors(file_name, FIRST_TRANSITION,
                                        line,lineCount, regLabels, entLabels, extLabels);

    if (*wasError == FALSE && lineError != NO_ERROR)
        *wasError = TRUE;

    if (*wasError == FALSE)
        firstAssemblerAlgo(line, regLabels, entLabels, extLabels, memoryImage, IC, DC);

    return lineError;
}

void firstAssemblerAlgo(const char *line,
                        NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                        MemoryImage *memoryImage, int *IC, int *DC)
{
    addToTablesIfNeededInFirstTran(line, regLabels, entLabels, extLabels, IC, DC);
    encodeLine(line, memoryImage, FIRST_TRANSITION);
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
void addToTablesIfNeededInFirstTran(const char *line,
                         NameTable *regLabels, NameTable *entLabels, NameTable *extLabels,
                         int *IC, int *DC)
{

}