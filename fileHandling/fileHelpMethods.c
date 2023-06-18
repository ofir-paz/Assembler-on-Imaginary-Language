/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist with handling files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "../errors/system_errors.h"
#include "../general_help_methods.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_CODE 0
/* ------------ */

/* Opens a file.
 * Terminates the program on error!
 * param const char *file_name is the name of the file to open
 * param const char *fileType is the type of the file to open
 * param const char *modeType is the mode to open the file with
 * Returns a pointer to the opened file. */
FILE *openFile(const char *file_name, const char *fileType, const char *modeType)
{
    static FILE *file = NULL; /* Will be the file to open */
    char *fileToOpen = connectTwoStrings(file_name, fileType); /* Full file name */

    if (file == NULL) /* If file was not opened */
    {
        file = fopen(fileToOpen, modeType); /* Open the file */
        handle_file_open_errors(file); /* Will handle errors with opening file */
    }

    free(fileToOpen); /* Freeing unnecessary string */
    return file;
}

/* Closes a file.
 * Terminates the program on error!
 * param FILE *file is the file to close
 * Returns nothing. */
void closeFile(FILE *file)
{
    handle_file_close_errors(fclose(file));
}