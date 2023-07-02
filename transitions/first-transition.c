/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdio.h>
#include <string.h>
#include "../new-data-types/process_result.h"
#include "../NameTable/NameTable.h"
#include "../encoding/MemoryImage.h"
#include "../errors/error_check.h"
#include "../general_help_methods.h"
#include "../FileHandling/readFromFile.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Main method of first transition stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return
 */
process_result first_transition(const char *file_name,
                                NameTable *entryLabels, NameTable *externLabels,
                                MemoryImage *codeMemImage, MemoryImage *dataMemImage)
{
    entryLabels = createNameTable(INT_TYPE); /* Will hold the .entry labels. */
    externLabels = createNameTable(INT_TYPE); /* Will hold the .extern labels. */

    return firstFileTraverse(file_name, entryLabels, externLabels, codeMemImage, dataMemImage);
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
process_result firstFileTraverse(const char *file_name,
                                 NameTable *entryLabels, NameTable *externLabels,
                                 MemoryImage *codeMemImage, MemoryImage *dataMemImage)
{
    boolean wasError = FALSE;
    char *line = NULL; /* This will hold the current line */

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, AFTER_MACRO, &line) != EOF)
    {
        if (isError(handleLine(line, entryLabels, externLabels,
                                      codeMemImage, dataMemImage, wasError)) == TRUE)
            wasError = TRUE;

        (void) free_ptr(POINTER(line)); /* Next line */
    }

    (void) free_ptr(POINTER(line));
}

/*
 * Handles the given line string in the pre-process.
 *
 * @param   *line Current line string.
 * @param   **macro_name Pointer to the current macro name.
 * @param   *amFile Data structure to hold the file to print.
 * @param   *macro_table Data structure to hold the macro names and contents.
 */
int handleLine(const char *line, NameTable *entryLabels, NameTable *externLabels,
                MemoryImage *codeMemImage, MemoryImage *dataMemImage, boolean wasError)
{

}