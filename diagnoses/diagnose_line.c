/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the functions that will be used to
 * diagnose the user's input.
 * */

/* ---Include header files--- */
#include <stdlib.h>
#include <string.h>
#include "../new-data-types/word_number.h"
#include "../new-data-types/param_num.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "../errors/system_errors.h"
#include "diagnose_help_methods.h"
#include "../general_help_methods.h"
/* -------------------------- */

/* -----Finals----- */
#define SPACE_FOR_NULL 1
#define DEFAULT_ZERO_LEN 0
/* ---------------- */

/* Gets the size of a specified word in a line string.
 * param const char *line is the line that's the word in it
 * param word_number wordNumber is the number of the word to seek the size of
 * Returns the size in size_t type. */
size_t getWordSize(const char *line, word_number wordNumber)
{
    int start = findStartIndexOfWord(line, wordNumber); /* Start index of the word */
    int end = nextEmptyIndex(line, start); /* End index of the word */

    return end - start; /* Returns the size (length) */
}

/* Finds a specified word in a given line string.
 * param const char *line is the line string that holds the word
 * param char **word is a pointer to the string that will hold the found word
 * param word_number wordNumber is the number of the word to seek, must be positive !
 * Returns nothing. */
void findWord(const char *line, char **word, word_number wordNumber)
{
    size_t wordSize = getWordSize(line, wordNumber); /* Finding the size of the word */
    int start = findStartIndexOfWord(line, wordNumber); /* Start index of the word */

    *word = (char *) allocate_space(wordSize); /* Allocating space for the string */
    (*word)[wordSize] = NULL_TERMINATOR; /* Add null terminator to the end of the string */

    /* Copying the command from line to string command */
    strncpy(*word, line + start, wordSize);
}

/* Finds index of parameter in const char *line.
 * param paramNum specifies the number of parameter to seek.
 * This functions presumes that the command and the commas (up to the parameter to find)
 * are valid since it is supposed to be called after they are validated.
 * Returns the index of the wanted parameter or index of last char ('\0') in line if there isn't. */
int findParamIndex(const char *line, param_num paramNum)
{
    /* Start index of the command in line. */
    int startOfCmd = nextCharIndex(line, MINUS_ONE_INDEX);

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
int getFloatParamLen(const char *line, param_num paramNum)
{
    int start = findParamIndex(line, paramNum); /* Start index of the float */
    int end = start + 1; /* End index of the float */
    while (isPartOfNumber(line, end) == TRUE) /* While end is still in the number */
        end++; /* Move end forward */
    return end - start; /* Return the length */
}

/* Finds the length of the parameter number paramNum with type paramtype pType
 * in const char *line.
 * Returns the length of the specific parameter. */
int findParamLen(const char *line, param_num paramNum)// paramtype pType)
{
    int len; /* Value to return */
    /* Addressing every option for the parameter type */
//    switch () {
//        case FLOAT: /* Option of float param */
//            len = getFloatParamLen(line, paramNum);
//            break;
//        case CHAR: /* Option of char param */
//            len = getCharParamLen();
//            break;
//        default: /* Extreme case */
//            len = DEFAULT_ZERO_LEN;
//    }
    return len;
}

/* Gets the float parameter numbered paramNum from param const char *line.
 * Returns the specified float value. */
float getFloatParamFromLine(const char *line, param_num paramNum)
{
    int index = findParamIndex(line, paramNum);
    char *endPtr;
    return (float) strtod(line + index, &endPtr);
}

/* Gets the char parameter numbered paramNum from param const char *line.
 * Returns the specified char. */
char getCharParamFromLine(const char *line, param_num paramNum)
{
    int index = findParamIndex(line, paramNum);
    return line[index];
}

/* Checks if the given line is an empty line (contains spaces and tabs only).
 * param const char *line is the line to check if it is empty or not
 * Returns TRUE if the line is empty, otherwise FALSE. */
boolean isEmptyLine(const char *line)
{
    return (getNextChar(line, MINUS_ONE_INDEX) == NULL_TERMINATOR)? TRUE : FALSE;
}

/* Checks if the given line is a comment line (first character is ';').
 * param const char *line is the line to check if it is a comment line
 * Returns TRUE if the line is a comment line, otherwise FALSE. */
boolean isCommentLine(const char *line)
{
    return (*line == SEMICOLON)? TRUE : FALSE;
}

/* Checks if the line needs to be skipped.
 * param const char *line is the line to check
 * Return TRUE if the line needs to be skipped, otherwise FALSE. */
boolean isSkipLine(const char *line)
{
    return (isEmptyLine(line) || isCommentLine(line) == TRUE)? TRUE : FALSE;
}
