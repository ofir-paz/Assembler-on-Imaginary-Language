/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the functions to handle the errors caught in error_check.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Error.h"
#include "complex.h"
#include "error_check.h"
/* -------------------------- */

/* ---Finals--- */
#define EXIT_CODE 0
#define SAME_STRINGS 0
#define ZERO_ITERATIONS 0
#define SPACE_FOR_NULL 1
#define DEFINED_VARIABLES 6
#define NO_FIX NULL
/* ------------ */

/* Prints the error message corresponding to the param Error error,
 * And the fix (if there is) specified by param const char *fix.
 * Returns nothing. */
void printERR(Error error, const char *fix)
{
    /* List of all the error messages.
     * Every index in this array represents the error from Error data type. */
    const char *errMSG[] = {
            /* System errors */
                            "ERR: Not enough space in the memory !",
            /* Function input errors */
                            "ERR: Functions in this program are case-sensitive !",
                            "ERR: Undefined function name !",
                            "ERR: Illegal comma after the command!",
            /* Comma input errors */
                            "ERR: Missing a comma !",
                            "ERR: Multiple consecutive commas !",
            /* Float param input error */
                            "ERR: There is missing a number parameter !",
                            "ERR: Missing number after sign !",
                            "ERR: The number parameter is illegal (not a number) !",
                            "ERR: There are too many dots in the number parameter !",
            /* Char param input error */
                            "ERR: There is missing a char parameter !",
                            "ERR: The char parameter has two or more characters in it !",
                            "ERR: The char parameter is not a letter !",
                            "ERR: The char parameter is not a capital letter !",
                            "ERR: The char parameter represents an undefined complex variable !",
            /* Extraneous text errors */
                            "ERR: Illegal comma after last parameter !",
                            "ERR: Extraneous text !",
            /* More errors */
                            "ERR: Exiting the program unsuccessfully ! (EOF before stop command)",
                            "ERR: Unknown error !",};

    puts(errMSG[error]); /* Prints the error message matching to the error type. */
    if (fix != NO_FIX)
        puts(fix);
}

/* Handles the error where there has been a failed allocation in the memory.
 * Returns nothing. */
void noAllocationERR()
{
    printERR(NO_SPACE_IN_MEM, NO_FIX); /* Prints the error */
    exit(EXIT_CODE); /* Terminates the program */
}

/* Handles the error where the user entered wrong case letters in the function's name.
 * The correct input is represented by param char **lowerCaseFunc.
 * Returns nothing. */
void caseSensitiveERR(char **lowerCaseFunc)
{
    char *fix, *tmp = "Try using the command: ";

    /* Assigning space in the memory for the fix string, including null */
    fix = (char *) malloc(strlen(tmp) + strlen(*lowerCaseFunc) + SPACE_FOR_NULL);

    if (isAllocated(fix) == FALSE) /* Checking if space has not been assigned. */
        noAllocationERR(); /* If not, noAllocationERR() will terminate the program */

    strcpy(fix, tmp); /* Adding tmp to fix */
    strcat(fix, *lowerCaseFunc); /* Adding lowerCaseFunc to fix */

    printERR(WRONG_CASE_FUNC, fix);

    /* Freeing the unneeded strings */
    free(*lowerCaseFunc);
    free(fix);
}

/* Handles the error where the command from the user is an undefined function.
 * Returns nothing. */
void undefinedFuncERR()
{
    printERR(UNDEFINED_FUNC, NO_FIX);
}

/* Handles the error where there is a comma after the function in the input.
 * Returns nothing. */
void commaAfterCmdERR()
{
    printERR(COMMA_AFTER_CMD, NO_FIX);
}

/* Handles an unknown error.
 * Should be called only in extreme cases !
 * Returns nothing. */
void unknownERR()
{
    printERR(GENERAL_ERR, NO_FIX);
}

/* Handles an invalid command with the given param Error cmdERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidCommand(Error cmdERR, char **fix)
{
    switch (cmdERR) {
        case WRONG_CASE_FUNC:
            caseSensitiveERR(fix);
            break;
        case UNDEFINED_FUNC:
            undefinedFuncERR();
            break;
        case COMMA_AFTER_CMD:
            commaAfterCmdERR();
            break;
        default:
            unknownERR();
    }
}

/* Handles invalid commas with the given param Error commaERR to indicate the error.
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidCommas(Error commaERR, char **fix)
{
    char *fixTemp = (fix == NULL)? NO_FIX : *fix ; /* fix can be NULL */
    printERR(commaERR, fixTemp);
}

/* Handles invalid param with the given param Error paramERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidParam(Error paramERR, char **fix)
{
    char *fixTemp = (fix == NULL)? NO_FIX : *fix ; /* fix can be NULL */
    printERR(paramERR, fixTemp);
}

/* Handles the extraneous text error by the given param Error extraERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleExtraneousERR(Error extraERR, char **fix)
{
    char *fixTemp = (fix == NULL)? NO_FIX : *fix ; /* fix can be NULL */
    printERR(extraERR, fixTemp);
}

void handle_lineTooLong_ERR(int lineIndex)
{
    printERR(LINE_TOO_LONG, lineIndex);
}



