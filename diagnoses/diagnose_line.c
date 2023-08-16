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

/*
 * Checks if the given string represents a valid integer.
 * Note: the integer can start with a plus or minus sign.
 *
 * @param   *str    The string to check for integer representation.
 *
 * @return  TRUE if the given string represents a valid integer, otherwise FALSE.
 */
boolean isStrInteger(const char *str)
{
    int currIndex = (isPlusOrMinus(str[ZERO_INDEX]))? ONE_INDEX : ZERO_INDEX;

    while (isCharNumber(str[currIndex++])); /* Go to the first char that is not a number. */

    /* Return TRUE if we reached '\0', otherwise FALSE. */
    return (str[currIndex] == NULL_TERMINATOR)? TRUE : FALSE;
}

/*
 * Checks if the given string represents a valid floating-point number.
 *
 * @param   *str    The string to check for floating-point representation.
 *
 * @return  TRUE if the given string represents a valid floating-point number, otherwise FALSE.
 */
boolean isStrFloat(const char *str)
{
    int currIndex = (isPlusOrMinus(str[ZERO_INDEX]))? ONE_INDEX : ZERO_INDEX;
    boolean wasDot = FALSE;

    /* While curr char is a number or there has been less than one dot. */
    while (isCharNumber(str[currIndex]))
    {
        if (str[currIndex] == DOT)
        {
            if (wasDot) /* If found a second dot, not a float. */
                break;
            else
                wasDot = TRUE;
        }
        currIndex++; /* Go to next char. */
    }

    /* Return TRUE if we reached '\0' and found a dot, otherwise FALSE. */
    return (str[currIndex] == NULL_TERMINATOR && wasDot)? TRUE : FALSE;
}

/*
 * Checks if there is a char that is not a comma or empty space after
 * a given index in the given line.
 *
 * @param   *line       The line to check for a char after the comma(s).
 * @param   commaIndex  The starting index to check for chars after it.
 *
 * @return  TRUE if there is a char after the given index that is not a comma or empty space,
 *          otherwise FALSE.
 */
boolean isCharAfterCommas(const char *line, int commaIndex)
{
    int currChar = commaIndex;

    /* While the chars are commas and we haven't reached end of line. */
    while (line[currChar] != NULL_TERMINATOR && line[currChar] == COMMA)
        currChar = nextCharIndex(line, currChar); /* Go to next char */

    return (line[currChar] != NULL_TERMINATOR)? TRUE : FALSE;
}
