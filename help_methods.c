/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Includes--- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "enums/neededKeys.h"
#include "errors/error_check.h"
#include "errors/error_handle.h"
/* -------------- */

/* ---Macros--- */
#define SAME_STRINGS 0
#define ZERO_COUNT 0
#define ZERO_INDEX 0
#define SIZE_FOR_NULL 1
/* ------------ */

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str)
{
    int i; /* Loop variable */
    
    /* Assigning space in the memory for the new string */
    char *lowerCase_str = (char *) malloc(strlen(str) + SIZE_FOR_NULL);
    lowerCase_str[strlen(str)] = NULL_TERMINATOR;

    if (isAllocated(lowerCase_str) == FALSE) /* Checking if space has been assigned. */
        noAllocationERR(); /* If not, noAllocationERR() will terminate the program */

    for (i = ZERO_INDEX; i < strlen(str); i++) /* Loop to go through all the chars in str */
        lowerCase_str[i] = (char) tolower(str[i]); /* Assigns the curr char as lower case */

    return lowerCase_str;
}

/* Returns the param int n + 1 */
int nextInt(int n)
{
    return n + 1;
}

/* Returns TRUE if param char ch is empty (space; tab; enter), otherwise FALSE */
boolean isEmpty(char ch)
{
    return ch == SPACE_KEY || ch == TAB_KEY || ch == ENTER_KEY;
}

/* Finds the next index in param const char *str where it is not an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next non-empty space in str (index of null if there isn't). */
int nextCharIndex(const char *str, int i)
{
    if (isIndexInStr(str, nextInt(i)) == TRUE) /* If the next index exists */
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
    if (isIndexInStr(str, nextInt(i)) == TRUE) /* If the next index exists */
    {
        /* Increasing i by 1 until we get to an index of char that is empty or null. */
        do
            i++; /* Go to the next index */
        while (isEmpty(str[i]) == FALSE && str[i] != NULL_TERMINATOR);

    }

    return i; /* Return the found index */
}

/* Finds the next index in param const char *str which points to a different word.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next word in str (index of null if there isn't) */
int nextWordIndex(const char *str, int i)
{
    /* Using the nextCharIndex and nextEmptyIndex funcs to find the next word. */
    return nextCharIndex(str, nextEmptyIndex(str, i));
}

/* Finds the next index in param const char *str where it is a comma.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next comma in str (index of null if there isn't) */
int nextCommaIndex(const char *str, int i)
{
    int index = i; /* Value to return */
    if (isIndexInStr(str, nextInt(i)) == TRUE) /* If the next index exists */
    {
        /* Increasing index by 1 until we get to an index of char that is a comma or null. */
        do
            index = nextCharIndex(str, index); /* Go to the next char index */
        while (str[index] != COMMA && str[index] != NULL_TERMINATOR);
    }
    return index; /* Returning the found index */
}

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2)
{
    return (strcmp(str1, str2) == SAME_STRINGS)? TRUE : FALSE;
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

/* Returns TRUE if the param char ch os a number, otherwise FALSE. */
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
    boolean isPartOfNumber = FALSE; /* Value to return, assume ch is not an element of a number. */
    if (isIndexInStr(str, index) == TRUE) {
        char ch = str[index];
        /* Check if ch is an element of a number */
        if (ch == PLUS || ch == MINUS || ch == DOT || isCharNumber(ch))
            isPartOfNumber = TRUE; /* Assign value to return to TRUE if so */
    }

    return isPartOfNumber;
}

/* Return the minimum of param int a and param int b. */
int getMin(int a, int b)
{
    return (a < b)? a : b;
}

/* Searches for the next empty space or comma in param const char *str
 * from the starting index param in index.
 * Return the index of the found empty space or comma, or end index of str if there are not. */
int nextEmptyCommaIndex(const char *str, int index)
{
    int nextCommaEmptyIndex; /* Value to return */
    int nextEmpty = nextEmptyIndex(str, index); /* Next empty index of str */
    int nextComma = nextCommaIndex(str, index); /* Next Comma index of str */
    nextCommaEmptyIndex = getMin(nextEmpty, nextComma); /* Taking the minimum of them */
    return nextCommaEmptyIndex;
}

char *connectTwoStrings(const char *str1, const char *str2)
{
    char *connectedString = (char *) malloc(strlen(str1) + strlen(str2) + 1);
    handle_allocation_error(connectedString);
    strcpy(connectedString, str1);
    connectedString = strcat(connectedString, str2);
    return connectedString;
}
