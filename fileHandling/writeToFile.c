/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file Has the functions to read and access data from files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_CODE 0
#define APPEND_MODE "a"
/* ------------ */

/* Writes a line to a file.
 * param const char *file_name is the name of the file to write to
 * param const char *fileType is the type of the file to write to
 * param const char *line is the line to write to the wanted file
 * Return nothing. */
void writeLineToFile(const char *file_name, const char *fileType, const char *line)
{
    /* Opening the file */
    FILE *fileToAddLineTO = openFile(file_name, fileType, APPEND_MODE);
    fputs(line, fileToAddLineTO); /* Printing to the file */
    closeFile(fileToAddLineTO); /* Closing the file */
}