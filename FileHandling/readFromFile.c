/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * This file has the methods to read and access data from files.
 */

/* ---Include header files--- */
#include <stdio.h>
#include "fileHelpMethods.h"
/* -------------------------- */

/* ---Finals--- */
#define UNABLE_TO_OPEN_FILE (-2)
#define ZERO_LEN 0
#define READ_MODE "r"
/* ------------ */

/*
 * Reads the next line from a given file.
 *
 * @param   *file_name      The name of the file to read from.
 * @param   *fileType       The type of the file to read from.
 * @param   **line          Pointer to string that will hold the read line.
 *
 * @return  The length of the line if it has been read successfully, EOF (-1) if the line
 *          was not read successfully, -2 if the file was not opened.
 */
ssize_t readNextLineFromFile(const char *file_name, const char *fileType, char **line)
{
    ssize_t returnCode = UNABLE_TO_OPEN_FILE; /* Return code to return, assume error. */
    FILE *fileToRead = openFile(file_name, fileType, READ_MODE); /* Open file */

    if (fileToRead != NULL) /* Read the line if the file was opened. */
    {
        size_t len = ZERO_LEN; /* Will be used with the getline() function */
        *line = NULL;

        /* Read the line. If there is no file to read, close the file. */
        if ((returnCode = getline(line, &len, fileToRead)) == EOF)
            closeFile(&fileToRead);
    }

    return returnCode;
}