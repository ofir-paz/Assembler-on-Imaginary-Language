/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Includes--- */
#include <string.h>
#include "../new-data-types/boolean.h"
#include "../new-data-types/word_number.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------- */

/* ---Macros--- */
#define MIN(a, b) ((a) < (b))? a : b
/* ------------ */

/* ---Finals--- */
#define ZERO_COUNT 0
/* ------------ */

/*
 * Finds the specified token in the given string and stores it in the provided pointer.
 *
 * @param   str         The input string containing tokens seperated by the given delim.
 * @param   word        A pointer to a char pointer that will store the found word.
 * @param   wordNumber  The position of the token to be extracted.
 *                      If wordNumber is negative or greater than the number of words in the line,
 *                      *word will be set to NULL.
 * @param   delim       The delim that separates the tokens in the string.
 */
void findTokenFromStr(const char *str, char **token, word_number tokenNumber, const char *delim)
{
    if (str != NULL && token != NULL && tokenNumber > ZERO_WORD) /* Check for invalid params. */
    {
        char *lineCopy, *rest, *tmpToken; /* Will be used to find the tokens. */
        int i = ZERO_INDEX; /* Loop variable. */

        lineCopy = my_strdup(str);
        rest = lineCopy;

        /* Finding the right word. */
        do tmpToken = strtok_r(rest, delim, &rest);
        while (++i < tokenNumber && token != NULL);

        *token = my_strdup(tmpToken);
        (void) free_ptr(POINTER(lineCopy));
    }
}

/* Checks if the param int i is an index of param const char *str.
 * Returns TRUE if i is an index of the given string, otherwise FALSE. */
boolean isIndexInStr(const char *str, int i)
{
    /* Note that strlen(str) is also an index, and the value is '\0'. */
    return (ZERO_INDEX <= i && i <= strlen(str))? TRUE : FALSE;
}

/* Returns TRUE if param char ch is empty (space; tab; enter), otherwise FALSE */
boolean isEmpty(char ch)
{
    return ch == SPACE_KEY || ch == TAB_KEY || ch == ENTER_KEY || ch == NULL_TERMINATOR;
}

/* Finds the next index in param const char *str where it is not an empty space (tab/space/enter).
 * If param int i is not an index of str returns i, otherwise returns
 * the index of the next non-empty space in str (index of null if there isn't). */
int nextCharIndex(const char *str, int i)
{
    if (isIndexInStr(str, i + ONE_INDEX) == TRUE) /* If the next index exists */
    {
        /* Increasing i by 1 until we get to an index of char that is a not empty or is null. */
        do
            i++; /* Go to the next index */
        while (isEmpty(str[i]) == TRUE && str[i] != NULL_TERMINATOR);
    }

    return i;
}

/* Finds the next index in param const char *str where it is an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next empty space in str (index of null if there isn't) */
int nextEmptyIndex(const char *str, int i)
{
    if (isIndexInStr(str, i + ONE_INDEX) == TRUE) /* If the next index exists */
    {
        /* Increasing i by 1 until we get to an index of char that is empty or null. */
        do
            i++; /* Go to the next index */
        while (isEmpty(str[i]) == FALSE && str[i] != NULL_TERMINATOR);

    }

    return i; /* Return the found index */
}

/*
 * Finds the next index in the given string which points to a different word.
 * If the given index is any negative value, returns the first word index.
 * If it's after the last char in the given string, returns the given index.
 *
 * @param   *str The line string.
 * @param   i The given index.
 * @return  The next word index from i in str, or i if i > len(str).
 */
int nextWordIndex(const char *str, int i)
{
    /* Using the nextCharIndex and nextEmptyIndex funcs to find the next word. */
    return (i < ZERO_INDEX)? nextCharIndex(str, MINUS_ONE_INDEX) :
        nextCharIndex(str, nextEmptyIndex(str, i));
}

/* Finds the next index in param const char *str where it is a comma.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next comma in str (index of null if there isn't) */
int nextCommaIndex(const char *str, int i)
{
    int index = i; /* Value to return */
    if (isIndexInStr(str, i + ONE_INDEX) == TRUE) /* If the next index exists */
    {
        /* Increasing index by 1 until we get to an index of char that is a comma or null. */
        do
            index = nextCharIndex(str, index); /* Go to the next char index */
        while (str[index] != COMMA && str[index] != NULL_TERMINATOR);
    }
    return index; /* Returning the found index */
}

/* Finds the start of a specific word in a given line string.
 * param const char *line is the line that holds the word
 * param word_number wordNumber is the number of the word to find its start index
 * Returns the found start index of the specific word in line. */
int findStartIndexOfWord(const char *line, word_number wordNumber)
{
    int start = MINUS_ONE_INDEX; /* Value to return */
    word_number currWord; /* Loop variable */

    /* Take start forward until it reaches the right word index */
    for (currWord = ZERO_WORD; currWord < wordNumber; currWord++)
        start = nextWordIndex(line, start);

    return start;
}

/* Gets the next non-empty char from a given index in a given string.
 * param const char *str is the string to seek for the next char in
 * param int i is the index to start the search from
 * Returns the next non-empty char, or 0 ('\0') if there isn't. */
char getNextChar(const char *str, int i)
{
    return str[nextCharIndex(str, i)];
}

/* Returns TRUE if const char ch = '+' or '-', otherwise FALSE. */
boolean isPlusOrMinus(char ch)
{
    return (ch == PLUS || ch == MINUS)? TRUE : FALSE;
}

/* Counts the dots in param const char *str from index
 * int start to index int end.
 * Return the amount of found dots. */
int countDots(const char *str, int start, int end)
{
    int cntDots = ZERO_COUNT; /* Dot counter, value to return. */
    int currIndex = start; /* Will be used to traverse through str */

    while (isIndexInStr(str, currIndex) && currIndex < end) {
        if (str[currIndex] == DOT) /* Check if we found a dot */
            cntDots++; /* Adding one to the counter */
        currIndex++;
    }
    return cntDots; /* Returning the counter */
}

/* Returns TRUE if the char in index int index of param const char *str
 * is a comma, otherwise FALSE. */
boolean isCurrCharComma(const char *str, int index)
{
    boolean isComma = FALSE; /* We assume the current char is not a comma */

    /* Checks if the index is an index of str and if the char is a comma */
    if (isIndexInStr(str, index) && str[index] == COMMA)
        isComma = TRUE; /* Assign the value to return to TRUE if so */

    return isComma;
}

/* Returns TRUE if the param char ch is a number, otherwise FALSE. */
boolean isCharNumber(char ch)
{
    boolean isNum = FALSE; /* We assume the current char is not a number */

    /* Checks if the index is an index of str and if the char is a number */
    if (ch >= CHAR_ZERO && ch <= CHAR_NINE)
        isNum = TRUE; /* Assign the value to return to TRUE if so */

    return isNum;
}

/* Returns TRUE if the char in index int index of param const char *str
 * is a number, otherwise FALSE. */
boolean isCurrCharNumber(const char *str, int index)
{
    return (isIndexInStr(str, index) == TRUE && isCharNumber(str[index]))? TRUE : FALSE;
}

/* Returns TRUE if the char in index int index of param const char *str
 * is a dot, otherwise FALSE. */
boolean isCurrCharDot(const char *str, int index)
{
    boolean isDot = FALSE; /* We assume the current char is not a dot */

    /* Checks if the index is an index of str and if the char is a dot */
    if (isIndexInStr(str, index) && str[index] == DOT)
        isDot = TRUE; /* Assign the value to return to TRUE if so */

    return isDot;
}

/* Returns TRUE if the char in param const char *str at index param int index is an
 * element of a number (+; -; .; 0-9), otherwise FALSE. */
boolean isPartOfNumber(const char *str, int index)
{
    boolean isPartOfNumber = FALSE; /* Value to return, assume ch is not a part of a number. */
    if (isIndexInStr(str, index) == TRUE) {
        char ch = str[index];
        /* Check if ch is an element of a number */
        if (ch == PLUS || ch == MINUS || ch == DOT || isCharNumber(ch))
            isPartOfNumber = TRUE; /* Assign value to return to TRUE if so */
    }

    return isPartOfNumber;
}

/* Searches for the next empty space or comma in param const char *str
 * from the starting index param in index.
 * Return the index of the found empty space or comma, or end index of str if there are not. */
int nextEmptyCommaIndex(const char *str, int index)
{
    int nextCommaEmptyIndex; /* Value to return */
    int nextEmpty = nextEmptyIndex(str, index); /* Next empty index of str */
    int nextComma = nextCommaIndex(str, index); /* Next Comma index of str */
    nextCommaEmptyIndex = MIN(nextEmpty, nextComma); /* Taking the minimum of them */
    return nextCommaEmptyIndex;
}