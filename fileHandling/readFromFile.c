/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file Has the functions to read and access data from files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <string.h>
#include "../general-enums/neededFinals.h"
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_CODE 0
#define READ_MODE "r"
/* ------------ */

/* Reads the next line from a given file.
 * param const char *file_name is the name of the file to read from
 * param const char *fileType is the type of the file to read from
 * param char **line is the string that will hold the read line
 * Returns o if the line is read successfully or EOF (-1) if not. */
int readNextLineFromFile(const char *file_name, const char *fileType, char **line)
{
    int returnCode = ZERO_CODE; /* Value to return */
    FILE *fileToRead = openFile(file_name, fileType, READ_MODE); /* Open file */

    if (fgets(*line, LINE_SIZE, fileToRead) == NULL)
    {
        closeFile(fileToRead);
        returnCode = EOF;
    }

    return returnCode;
}