/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * diagnose_util.c
 *
 * This file has the help method for diagnosing strings.
 */

/* ---Includes--- */
#include <string.h>
#include "../new-data-types/boolean.h"
#include "../new-data-types/word_number.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "../util/memoryUtil.h"
#include "../util/numberUtil.h"
#include "../util/stringsUtil.h"
/* -------------- */

/* ---Finals--- */
#define ZERO_COUNT 0
/* ------------ */

/* ---Macros--- */
#define MIN(a, b) ((a) < (b))? a : b
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
        (void) clear_ptr(lineCopy)
    }
}

/*
 * Checks if the given index parameter is an index of the given string.
 * (Index of null-terminator is also accepted)
 *
 * @param   *str    The string to check if the index is a part of.
 * @param   i       The index to check for its validity.
 *
 * @return  TRUE if the given index is an index of the given string, otherwise FALSE.
 */
boolean isIndexInStr(const char *str, int i)
{
    /* Note that strlen(str) is also an index, and the value is '\0'. */
    return (ZERO_INDEX <= i && i <= strlen(str))? TRUE : FALSE;
}

/*
 * Checks if a given char is an empty space char.
 * Empty space counts as space, tab, enter or null-terminator.
 *
 * @param   ch  The char to check if it's empty.
 *
 * @return  TRUE if the given char is empty (space; tab; enter; '\0'), otherwise FALSE.
 */
boolean isEmpty(char ch)
{
    return ch == SPACE_KEY || ch == TAB_KEY || ch == ENTER_KEY || ch == NULL_TERMINATOR;
}

/*
 * Finds the index of the next character in a string starting from a given index.
 * The meaning of the next char is the next non-empty character.
 *
 * @param   *str    The input string.
 * @param   i       The starting index.
 *
 * @return  The index of the next character, or index of null-terminator
 *          if the end of the string is reached.
 */
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

/*
 * Finds the index of the next empty space (whitespace) in a string starting from a given index.
 * white spaces can be space, tab, enter or null-terminator.
 *
 * @param   *str    The input string.
 * @param   i       The starting index.
 *
 * @return  The index of the next empty space.
 */
int nextEmptyIndex(const char *str, int i)
{
    if (isIndexInStr(str, i + ONE_INDEX) == TRUE) /* If the next index exists */
    {
        /* Increasing i by 1 until we get to an index of char that is empty or null. */
        do
            i++; /* Go to the next index */
        while ((isEmpty(str[i]) == FALSE || str[i] == ENTER_KEY) && str[i] != NULL_TERMINATOR);

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
 *
 * @return  The next word index from i in str, or i if i > len(str).
 */
int nextWordIndex(const char *str, int i)
{
    /* Using the nextCharIndex and nextEmptyIndex funcs to find the next word. */
    return (i < ZERO_INDEX)? nextCharIndex(str, MINUS_ONE_INDEX) :
        nextCharIndex(str, nextEmptyIndex(str, i));
}

/*
 * Finds the index of the next occurrence of a specific character
 * in a string starting from a given index.
 *
 * @param   *str    The input string.
 * @param   i       The starting index.
 * @param   ch      The specific character to search for.
 *
 * @return  The index of the next occurrence of the specified character,
 *          or index of '\0' if the character is not found.
 */
int nextSpecificCharIndex(const char *str, int i, char ch)
{
    int index = i; /* Value to return */
    if (isIndexInStr(str, i + ONE_INDEX) == TRUE) /* If the next index exists */
    {
        /* Increasing index by 1 until we get to an index of char that is ch or null. */
        do
            index = nextCharIndex(str, index); /* Go to the next char index */
        while (str[index] != ch && str[index] != NULL_TERMINATOR);
    }
    return index; /* Returning the found index */
}

/*
 * Finds the starting index of a specific word within a given line of text.
 *
 * @param   *line       The input line of text.
 * @param   wordNumber  The ordinal number of the word to find (1-based index).
 *
 * @return  The starting index of the specified word within the line,
 *          or index of '\0' if the word does not exist.
 */
int findStartIndexOfWord(const char *line, word_number wordNumber)
{
    int start = MINUS_ONE_INDEX; /* Value to return */
    word_number currWord; /* Loop variable */

    /* Take start forward until it reaches the right word index */
    for (currWord = ZERO_WORD; currWord < wordNumber; currWord++)
        start = nextWordIndex(line, start);

    return start;
}

/*
 * Gets the next non-empty char from a given index in a given string.
 *
 * @param   *str    The string to seek for the next char in.
 * @param   i       The index to start the search from.
 *
 * @return  The next non-empty char, or 0 ('\0') if there isn't.
 */
char getNextChar(const char *str, int i)
{
    return str[nextCharIndex(str, i)];
}

/*
 * Checks if a given character is a plus or minus sign.
 *
 * @param   ch  The character to check if it's a plus or minus sign.
 *
 * @return  TRUE if ch = '+' or ch = '-', otherwise FALSE.
 */
boolean isPlusOrMinus(char ch)
{
    return (ch == PLUS || ch == MINUS)? TRUE : FALSE;
}

/*
 * Checks if a given char is an english letter.
 *
 * @param   ch  The char to check if it's a letter.
 *
 * @return  TRUE if ch is a letter, otherwise FALSE.
 */
boolean isLetter(char ch)
{
    return (between(ch, CHAR_a, CHAR_z) || between(ch, CHAR_A, CHAR_Z))? TRUE : FALSE;
}

/*
 * Checks if a given character is a number.
 *
 * @param   ch  The character to check if it's a number.
 *
 * @return  TRUE if ch is a number, otherwise FALSE.
 */
boolean isCharNumber(char ch)
{
    return between(ch, CHAR_ZERO, CHAR_NINE);
}

/*
 * Checks if a given char is a legal character (letter or number).
 *
 * @param   ch  The given character to check if it's a legal character.
 *
 * @return  TRUE if ch is a legal character, otherwise FALSE.
 */
boolean isLegalChar(char ch)
{
    return (isLetter(ch) || isCharNumber(ch))? TRUE : FALSE;
}

/*
 * Checks if a character at a specified index within a string is part of a number.
 *
 * @param   *str    The input string.
 * @param   index   The index of the character to check.
 *
 * @return  TRUE if the character at the specified index is part of a number, otherwise FALSE.
 */
boolean isPartOfNumber(const char *str, int index)
{
    boolean isPartOfNumber = FALSE; /* Value to return, assume ch is not a part of a number. */
    if (isIndexInStr(str, index) == TRUE) {
        char ch = str[index];
        /* Check if ch is an element of a number */
        if (isPlusOrMinus(ch) || isCharNumber(ch))
            isPartOfNumber = TRUE; /* Assign value to return to TRUE if so */
    }

    return isPartOfNumber;
}

/*
 * Searches for the next empty space or comma in the given string.
 *
 * @param   *str    The string to check for the first empty space or comma in.
 * @param   index   The index to start the search from.
 *
 * @return  The index of the found empty space or comma, or end index of str if there are not.
 */
int nextEmptyCommaIndex(const char *str, int index)
{
    int nextCommaEmptyIndex; /* Value to return */
    int nextEmpty = nextEmptyIndex(str, index); /* Next empty index of str */
    int nextComma = nextSpecificCharIndex(str, index, COMMA); /* Next Comma index of str */
    nextCommaEmptyIndex = MIN(nextEmpty, nextComma); /* Taking the minimum of them */
    return nextCommaEmptyIndex;
}