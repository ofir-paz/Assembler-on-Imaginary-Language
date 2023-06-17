/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains functions to check errors
 * that can occur in the program.
 * This file handles system errors, so if any system error is caught,
 * the program will be terminated !
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "error_types/SystemError.h"
/* -------------------------- */

/* Prints an error message regarding the given error and terminating the program.
 * param SystemError sysErr is the given error type.
 * Returns nothing. */
void system_error(SystemError sysErr)
{
    /* This array of strings holds all the system related error messages that can be used. */
    const char *systemErrorMsg[] =
            {
            "ERR: no error",
                    /* Dynamic space allocation errors */
            "ERR: Not enough space in the memory !",
                    /* File handling related errors */
            "ERR: error with opening a file !",
            "ERR: error with closing a file !"
            };

    puts(systemErrorMsg[sysErr]); /* Printing the error */
    exit(EXIT_FAILURE); /* Terminating the program */
}

/* Handles no allocation error.
 * param void *ptr is the pointer to check if it has allocated space
 * Returns nothing. */
void handle_allocation_error(void *ptr)
{
    if (ptr == NULL) /* == NULL, means the space is not allocated */
        system_error(NO_ALLOCATION_ERR);
}

/* Handles error with opening a file.
 * param const FILE *file is the stream to check if it has been opened
 * Returns nothing. */
void handle_file_open_errors(const FILE *file)
{
    if (file == NULL)
        system_error(FILE_OPEN_ERR);
}

/* Handles error with closing a file.
 * param int code is the return code of fclose() func.
 * Returns nothing. */
void handle_file_close_errors(int code)
{
    if (!code) /* != 0, 0 is success return code of fclose() */
        system_error(FILE_CLOSE_ERR);
}