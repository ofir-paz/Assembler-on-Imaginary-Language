/*
 * @author Ofir Paz
 * @version (18/08/2023)
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
 * @param   *file_name      The name of the file to write to.
 * @param   *fileType       The type of the file to write to.
 * @param   *text           The text to write to the wanted file.
 */
void writeToFile(const char *file_name, const char *fileType, const char *text)
{
    if (text != NULL) /* If we need to print anything. */
    {
        FILE *fileToWriteTo = openFile(file_name, fileType, WRITE_MODE); /* Open the file */

        if (fileToWriteTo != NULL) /* Check if the file was opened. */
        {
            fputs(text, fileToWriteTo); /* Printing to the file */
            closeFile(&fileToWriteTo); /* Closing the file */
        }
    }
}