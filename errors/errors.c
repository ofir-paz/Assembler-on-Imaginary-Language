/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdio.h>
#include <stdarg.h>
#include "../new-data-types/boolean.h"
#include "error_types/error_types.h"
#include "PreProcessorErrors/PreProcessorErrors.h"
#include "error_check.h"
#include "error_handle.h"
/* -------------------------- */

/* ---Finals--- */

/* ANSI escape codes for text color */
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BLUE     "\x1B[34m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#define INPUT_ERROR_CODE (-1)
/* ------------ */

void print_assembler_ERR(Error error, const char *file_name, int lineNumber)
{
    /* Arrays to hold all the different error messages. */
    const char *imgSystemErrorMSG[] =
            {
                "NO_ERROR",
            };
    const char *syntaxErrorMSG[] =
            {
                    "NO_ERROR",
                    "Invalid macro name!! a macro name cannot be a saved word.",
                    "Extraneous text in a macro definition line !!"
            };
    const char *logicalErrorMSG[] =
            {
                    "NO_ERROR",
                    ""
            };
    const char **errorMSG[] = {imgSystemErrorMSG, syntaxErrorMSG, logicalErrorMSG};

    /* Printing the errors. */
    fprintf(stderr, ANSI_COLOR_RED "\nERROR: " ANSI_COLOR_RESET "%s\n",
            errorMSG[(error / MAX_ERRORS_IN_ENUM) - 1][error % MAX_ERRORS_IN_ENUM]);
    fprintf(stderr, ANSI_COLOR_BLUE "In file: " ANSI_COLOR_RESET "%s, "
                    ANSI_COLOR_BLUE "On line: " ANSI_COLOR_RESET "%d\n", file_name, lineNumber);
}

Error handle_lineTooLong_error(const char *line, int lineIndex)
{
    Error error = NO_ERROR;

    if (isLineTooLong(line) == TRUE)
    {
        handle_lineTooLong_ERR(lineIndex);
        error = 1;//LINE_TOO_LONG_ERR;
    }

    return error;
}