/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file Has the functions to read and access data from files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "../general-enums/neededFinals.h"
#include "../errors/errors.h"
#include "../help_methods.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_CODE 0
/* ------------ */

FILE *openFile(const char *file_name, const char *fileType, const char *modeType)
{
    static FILE *file; /* Will be the file to open */
    char *fileToOpen = connectTwoStrings(file_name, fileType);

    if (file == NULL) /* If file was not opened */
    {
        file = fopen(fileToOpen, modeType); /* Open the file */
        handle_file_open_errors(file); /* Will handle errors with opening file  */
    }

    free(fileToOpen); /* Freeing unnecessary string */
    return file;
}

void closeFile(FILE *file)
{
    handle_file_close_errors(fclose(file));
}