/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains functions to check errors regarding the operating system
 * that can occur in the program.
 *
 * This file handles system errors, so if any system error is caught,
 * the program will be terminated !
 */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "error_types/SystemError.h"
/* -------------------------- */

/*
 * Prints an error message regarding the given error and terminating the program.
 *
 * @param   sysErr  The system error to print.
 */
void system_error(SystemError sysErr)
{
    /* This array of strings holds all the system related error messages that can be used. */
    const char *systemErrorMsg[] =
            {
            "ERR: no error",
                    /* Dynamic space allocation errors */
            "ERR: Not enough space in the memory !",
                    /* File handling related errors */
            "ERR: error with closing a file !"
            };

    puts(systemErrorMsg[sysErr]); /* Printing the error */
    exit(EXIT_FAILURE); /* Terminating the program */
}

/*
 * Handles no allocation error.
 *
 * @param   *ptr     The pointer to check if it has allocated space.
 */
void handle_allocation_error(void *ptr)
{
    if (ptr == NULL) /* == NULL, means the space is not allocated */
        system_error(NO_ALLOCATION_ERR);
}

/*
 * Handles error with closing a file.
 *
 * @param   code    The return code of fclose() func.
 */
void handle_file_close_errors(int code)
{
    if (code == EOF) /* EOF (-1) is error return code of fclose() */
        system_error(FILE_CLOSE_ERR);
}