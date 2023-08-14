/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdio.h>
#include "error_types/error_types.h"
/* -------------------------- */

/* ---Finals--- */

/* ANSI escape codes for text color */
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BLUE     "\x1B[34m"
#define ANSI_COLOR_RESET    "\x1b[0m"

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
                    /* Indicates no error. !! add new errors after this one !! */
                "NO_ERROR",
                    /* Macro related syntax errors */
                "Invalid macro name! a macro name cannot be a saved word.",
                "Extraneous text in a macro definition line !!",
                    /* Label related syntax errors */
                    "Expected label name !!",
                    "Empty space between label and colon! Label and colon can't be seperated.",
                    "Label starts with a number! It must start with a letter.",
                    "Label starts with an illegal character! It must start with a letter.",
                    "Label Contains illegal characters! It can include only letters and numbers.",
                    "Label Is too long! Max label length is 31 characters long.",
                    "Label Is a saved word! A label name cannot be a saved word."

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