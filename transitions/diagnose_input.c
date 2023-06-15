/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the functions that will be used to
 * diagnose the user's input.
 * */

/* ---Include header files--- */
#include <stdlib.h>
#include <string.h>
#include "../new-data-types/Error.h"
#include "../general-enums/neededKeys.h"
#include "error_check.h"
#include "error_handle.h"
#include "cmd_params.h"
#include "FunctionPtr.h"
#include "paramType.h"
#include "help_methods.h"
#include "handle_command.h"
/* -------------------------- */

/* -----Macros----- */
#define MINUS_ONE_INDEX (-1)
#define ZERO_INDEX 0
#define ONE_INDEX 1
#define SPACE_FOR_NULL 1
#define CHAR_PARAM_LEN 1
#define DEFAULT_ZERO_LEN 0
/* ---------------- */

/* Gets the command's size from the input line. Returns it in size_t type */
size_t getCommandSize(const char *line)
{
    /* Command starts with a non-empty space and ends with an empty space. */
    int start = nextCharIndex(line, MINUS_ONE_INDEX); /* Start index of command. */
    int end = nextEmptyIndex(line, start); /* End index of command. */

    return end - start; /* Returns the size (length) */
}

/* Finds the command (function to use) from the input param const char *line and
 * sets the param **command to the found command.
 * Returns nothing. */
void findCommand(const char *line, char **command)
{
    size_t cmdSize = getCommandSize(line); /* Finding the size of the command */
    int start = nextCharIndex(line, MINUS_ONE_INDEX); /* Start index of command */

    *command = (char *) malloc(cmdSize + SPACE_FOR_NULL); /* Assigning space for the string */
    if (isAllocated(*command) == FALSE) /* Checking if space has been assigned. */
        noAllocationERR(); /* If not, noAllocationERR() will terminate the program */

    (*command)[cmdSize] = NULL_TERMINATOR; /* Adding null terminator to the end of the string */

    /* Copying the command from line to string command */
    strncpy(*command, line + start, cmdSize);
}

/* Finds which handle function param const char *command matches with.
 * Return a pointer to the function, or NULL if it doesn't match with any. */
FunctionPtr getFunction(const char *command)
{
    /* map of the defined functions.
     * !! To insert new functions you must insert them before NULL !! */
    const struct {
        const char *name;
        FunctionPtr function;
    } functionMap[] =
            {
                    {"read_comp", handle_read_comp},
                    {"print_comp", handle_print_comp},
                    {"add_comp", handle_add_comp},
                    {"sub_comp", handle_sub_comp},
                    {"mult_comp_real", handle_mult_comp_real},
                    {"mult_comp_img", handle_mult_comp_img},
                    {"mult_comp_comp", handle_mult_comp_comp},
                    {"abs_comp", handle_abs_comp},
                    {"stop", handle_stop},
                    {NULL, NULL}
            };

    FunctionPtr funcToReturn = NULL; /* ptr to functions to return */
    int i = ZERO_INDEX; /* Loop variable */

    while (functionMap[i].name != NULL && funcToReturn == NULL) {
        /* Checks if the string command matches with defined function */
        if (sameStrings(command, functionMap[i].name) == TRUE)
            /* Assign the value to return to the handle function pointer */
            funcToReturn = functionMap[i].function;
        i++; /* Checks next function */
    }

    return funcToReturn;
}

/* Given the param const char *command and the param Error error,
 * Returns a string contains a suggested fix for the error in the command. */
char *getCmdFix(const char *command, Error error)
{
    char *fix; /* String to return, will contain the fix. */
    switch (error) {
        case WRONG_CASE_FUNC:
            fix = strToLowerCase(command); /* The fix here is the lower case command */
            break;
        default:
            fix = NULL; /* No fix to be found, String to return will be NULL. */
    }
    return fix;
}

/* Finds index of parameter in const char *line.
 * param paramNum specifies the number of parameter to seek.
 * This functions presumes that the command and the commas (up to the parameter to find)
 * are valid since it is supposed to be called after they are validated.
 * Returns the index of the wanted parameter or index of last char ('\0') in line if there isn't. */
int findParamIndex(const char *line, ParamNum paramNum)
{
    int startOfCmd = nextCharIndex(line, MINUS_ONE_INDEX); /* Start index of the command in line. */

    /* Here we make the assumption on the command's validation. */
    int index = nextWordIndex(line, startOfCmd); /* Start from first parameter */

    int j; /* Loop variable */

    /* In this loop we take index to the next parameter until we get to the wanted parameter.
     * We also start the loop from 1 because index already points to the first parameter in line.
     * We assume here that the commas are valid up to the parameter to find. */
    for (j = ONE_INDEX; j < paramNum; j++)
        /* Assign the index to the last index of the curr param */
        index = nextCharIndex(line, nextCommaIndex(line, index));

    return index;
}

/* Finds the length of the float parameter numbered paramNum in
 * param const char *line.
 * Returns the length of the specified float parameter. */
int getFloatParamLen(const char *line, ParamNum paramNum)
{
    int start = findParamIndex(line, paramNum); /* Start index of the float */
    int end = start + 1; /* End index of the float */
    while (isPartOfNumber(line, end) == TRUE) /* While end is still in the number */
        end++; /* Move end forward */
    return end - start; /* Return the length */
}

/* Returns the length of a char param. */
int getCharParamLen()
{
    return CHAR_PARAM_LEN; /* Char is always with length 1. */
}

/* Finds the length of the parameter number paramNum with type paramtype pType
 * in const char *line.
 * Returns the length of the specific parameter. */
int findParamLen(const char *line, ParamNum paramNum, paramtype pType)
{
    int len; /* Value to return */
    /* Addressing every option for the parameter type */
    switch (pType) {
        case FLOAT: /* Option of float param */
            len = getFloatParamLen(line, paramNum);
            break;
        case CHAR: /* Option of char param */
            len = getCharParamLen();
            break;
        default: /* Extreme case */
            len = DEFAULT_ZERO_LEN;
    }
    return len;
}

/* Gets the float parameter numbered paramNum from param const char *line.
 * Returns the specified float value. */
float getFloatParamFromLine(const char *line, ParamNum paramNum)
{
    int index = findParamIndex(line, paramNum);
    char *endPtr;
    return (float) strtod(line + index, &endPtr);
}

/* Gets the char parameter numbered paramNum from param const char *line.
 * Returns the specified char. */
char getCharParamFromLine(const char *line, ParamNum paramNum)
{
    int index = findParamIndex(line, paramNum);
    return line[index];
}

