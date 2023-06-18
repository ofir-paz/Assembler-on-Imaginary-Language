/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the methods to write to files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define APPEND_MODE "a"
/* ------------ */

/* appends text to file.
 * param const char *file_name is the name of the file to append to
 * param const char *fileType is the type of the file to append to
 * param const char *text is the text to append to the wanted file
 * Return nothing. */
void appendToFile(const char *file_name, const char *fileType, const char *text)
{
    FILE *fileToAppendTo = openFile(file_name, fileType, APPEND_MODE); /* Open the file */
    fprintf(fileToAppendTo, "%s", text); /* Printing to the file */
    closeFile(fileToAppendTo); /* Closing the file */
}