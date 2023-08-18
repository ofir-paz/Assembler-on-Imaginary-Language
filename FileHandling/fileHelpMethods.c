/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has help methods to assist with handling files.
 */

/* ---Include header files--- */
#include <stdio.h>
#include <string.h>
#include "../errors/system_errors.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Finals--- */
#define BUFFER 256
/* ------------ */

/*
 * Opens a file.
 *
 * @param   *file_name The name of the file to open.
 * @param   *fileType The type of the file to open.
 * @param   *modeType The mode to open the file with.
 *
 * @return  Pointer to the opened file.
 */
FILE *openFile(const char *file_name, const char *fileType, const char *modeType)
{
    static FILE *file = NULL; /* Will be the file to open */
    static char currFileName[BUFFER];
    static char currModeType[BUFFER];
    char *fileToOpen = connectTwoStrings(file_name, fileType); /* Full file name */

    /* If we open a different file or open the same one but in different type */
    if (sameStrings(currFileName, fileToOpen) == FALSE  ||
        sameStrings(currModeType, modeType) == FALSE)
    {
        file = fopen(fileToOpen, modeType); /* Open the file */
        if (file == NULL)
            printf("\nUnable to open file: \"%s\"\n", file_name);

        (void) strcpy(currFileName, fileToOpen);
        (void) strcpy(currModeType, modeType);
    }

    (void) clear_ptr(fileToOpen) /* Freeing unnecessary string */
    return file;
}

/*
 * Closes a file.
 * Terminates the program on error!
 *
 * @param   **file Pointer to the file to close.
 */
void closeFile(FILE **file)
{
    if (file != NULL && *file != NULL) /* Close the file only if it's open */
        handle_file_close_errors(fclose(*file));
    *file = NULL;
}