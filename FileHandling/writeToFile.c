/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * This file has the methods to write to files.
 */

/* ---Include header files--- */
#include <stdio.h>
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define WRITE_MODE "w"
/* ------------ */

/*
 * Writes text to a given file.
 *
 * @param   *file_name The name of the file to append to.
 * @param   *fileType The type of the file to append to.
 * @param   *text The text to append to the wanted file.
 */
void writeToFile(const char *file_name, const char *fileType, const char *text)
{
    FILE *fileToAppendTo = openFile(file_name, fileType, WRITE_MODE); /* Open the file */
    fprintf(fileToAppendTo, "%s", text); /* Printing to the file */
    closeFile(fileToAppendTo); /* Closing the file */
}