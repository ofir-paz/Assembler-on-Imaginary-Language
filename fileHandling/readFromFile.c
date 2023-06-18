/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the methods to read and access data from files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_LEN 0
#define READ_MODE "r"
/* ------------ */

/* Reads the next line from a given file.
 * param const char *file_name is the name of the file to read from
 * param const char *fileType is the type of the file to read from
 * param char **line is a pointer to string that will hold the read line
 * Returns the length of the line if it has been read successfully or EOF (-1) if not. */
int readNextLineFromFile(const char *file_name, const char *fileType, char **line)
{
    int returnCode; /* Value to return, we assume success */
    FILE *fileToRead = openFile(file_name, fileType, READ_MODE); /* Open file */
    size_t len = ZERO_LEN; /* Will be used with the getline() function */
    *line = NULL;

    /* Read the line. If there is no file to read, close the file. */
    if ((returnCode = (int) getline(line, &len, fileToRead)) == EOF)
        closeFile(fileToRead);

    return returnCode;
}