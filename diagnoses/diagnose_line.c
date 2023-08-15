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
#include "../general-enums/programFinals.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "diagnose_util.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* -----Finals----- */
#define EMPTY_DELIM " \t\n"
/* ---------------- */

/*
 * Finds the specified word in the given line and stores it in the provided pointer.
 *
 * @param   line        The input line containing words separated by spaces.
 * @param   word        A pointer to a char pointer that will store the found word.
 * @param   wordNumber  The position of the word to be extracted.
 *                      If wordNumber is negative or greater than the number of words in the line,
 *                      *word will be set to NULL.
 */
void findWord(const char *line, char **word, word_number wordNumber)
{
    findTokenFromStr(line, word, wordNumber, EMPTY_DELIM);
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
