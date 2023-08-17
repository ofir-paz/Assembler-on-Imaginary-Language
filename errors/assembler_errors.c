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

/* ---------------Prototypes--------------- */
void print_assembler_ERR(Error error, const char *file_name, int lineNumber);
/* ---------------------------------------- */

/*
 * Handles an assembler error.
 *
 * @param   *file_name      The name of the file where the error occurred.
 * @param   lineNumber      The line number where the error occurred.
 * @param   lineError       The specific error that occurred.
 */
void handle_assembler_error(const char *file_name, int lineNumber, Error lineError)
{
    print_assembler_ERR(lineError, file_name, lineNumber);
}

void print_assembler_ERR(Error error, const char *file_name, int lineNumber)
{
    /* Arrays to hold all the different error messages. */
    const char *imgSystemErrorMSG[IMG_SYSTEM_ERROR_SIZE - IMG_SYSTEM_ERR_START] =
            {
                    /* Indicates no error. !! add new errors after this one !! */
                "NO_ERROR",

                    /* Memory limitations errors */
                "Line overflow error! A line must be 80 or less characters long.",
                "Instant value overflow error! Instant value must be: -512 <= x <= 511.",
                "Data value overflow error! Data value must be: -2048 <= x 2047.",
            };

    const char *syntaxErrorMSG[SYNTAX_ERROR_SIZE - SYNTAX_ERR_START] =
            {
                    /* Indicates no error. !! add new errors after this one !! */
                "NO_ERROR",
                    /* Macro related syntax errors */
                "Expected macro!",
                "Invalid macro name! a macro name cannot be a saved word.",
                "Extraneous text in a macro definition line !!",

                    /* Label related syntax errors */
                "Expected label name !!",
                "Empty space between label and colon! Label and colon can't be seperated.",
                "Label starts with a number! It must start with a letter.",
                "Label starts with an illegal character! It must start with a letter.",
                "Label Contains illegal characters! It can include only letters and numbers.",
                "Label Is too long! Max label length is 31 characters long.",
                "Label Is a saved word! A label name cannot be a saved word.",
                "Multiple consecutive colons after label name! Label definition needs one colon.",
                "Unneeded comma after label definition!",

                    /* Command syntax errors */
                "Expected command (operation or guidance)!",
                "Unneeded comma after command!",

                    /* Guidance syntax errors. */
                "Expected guidance after dot!",
                "Multiple consecutive dots in guidance!",
                "Guidance name is wrong case (try to use lower case letters)!",
                "Undefined guidance!",

                    /* Operation syntax errors. */
                "Expected dot before guidance!",
                "Operation is wrong case (try to use lower case letters)!",
                "Undefined operation!",

                    /* General argument errors. */
                "Expected comma and argument!",
                "Expected comma!",
                "Expected argument!",
                "Multiple consecutive commas!",

                    /* String argument syntax errors. */
                "Expected open quotes in string argument!",
                "Expected closing quotes in string argument!",
                "String contains unprintable characters!",

                    /* Instant value argument syntax errors. */
                "Number is only a sign!",
                "Multiple consecutive signs in number argument!",
                "Number is not an integer! This machine supports only integers.",
                "Supposed value is an illegal number!",

                    /* Label argument syntax errors. */
                "Supposed label argument is too long! Max label name length is 31.",
                "Illegal characters in supposed label argument!",

                    /* Register argument syntax errors.*/
                "Expected register argument!",
                "Multiple consecutive ats ('@') !",
                "Expected register letter! Register letter is the letter 'r'.",
                "Capital register letter! Try to use 'r' instead of 'R'.",
                "Wrong register letter! The only register letter is 'r'.",
                "Expected register number!",
                "Illegal register number! Register numbers range from 0 to 7.",
                "Extraneous text after register argument! Try to remove text after @rx (x=number)",

                    /* Extraneous text errors */
                "Extraneous comma!",
                "Extraneous text!",
                "Expected comma (or might be extraneous text)!",
                "Expected argument after last comma (or might be extraneous comma)!"
            };

    const char *logicalErrorMSG[] =
            {
                    /* Indicates no error. !! add new errors after this one !! */
                "NO_ERROR",

                    /* Label related logical errors. */
                "Label already defined! Try to use a different label name.",

                    /* Guidance related logical errors. */
                "Argument is not a label! Expected a label name argument.",
                "Argument is not a number! Expected a data number argument!",

                    /* Addressing methods related logical errors. */
                "Illegal addressing method for destination argument!",
                "Illegal addressing method for source argument!",

                    /* Entry label related logical errors */
                "Label was already defined as entry label!",

                    /* Extern label related logical errors */
                "Label was already defined as external label!",

                    /* Label tables related logical errors */
                "Label was defined in the file and is external!",
                "Label was defined both as entry and extern!"
            };
    const char **errorMSG[] = {imgSystemErrorMSG, syntaxErrorMSG, logicalErrorMSG};

    /* Printing the errors. */
    fprintf(stderr, ANSI_COLOR_RED "\nERROR: " ANSI_COLOR_RESET "%s\n",
            errorMSG[(error / MAX_ERRORS_IN_ENUM) - 1][error % MAX_ERRORS_IN_ENUM]);

    fprintf(stderr, ANSI_COLOR_BLUE "In file: " ANSI_COLOR_RESET "\"%s\", "
                    ANSI_COLOR_BLUE "On line: " ANSI_COLOR_RESET "%d\n", file_name, lineNumber);
}