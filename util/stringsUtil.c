/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../new-data-types/boolean.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "memoryUtil.h"
#include "numberUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define SAME_STRINGS 0
#define SIZE_FOR_NEW_LINE 1
#define SIZE_FOR_TAB 1
#define SIZE_FOR_STR 30
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Creates a dynamically allocated string from a given string.
 *
 * @param   *str The string to recreate dynamically.
 * @return  The newly dynamically created string with the contents of str.
 */
char *getDynamicString(char *str)
{
    char *dynamicString = (char *) allocate_space(strlen(str) + SIZE_FOR_NULL);
    (void) strcpy(dynamicString, str);
    return dynamicString;
}

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str)
{
    int i; /* Loop variable */

    /* Assigning space in the memory for the new string */
    char *lowerCase_str = (char *) allocate_space(strlen(str) + SIZE_FOR_NULL);

    lowerCase_str[strlen(str)] = NULL_TERMINATOR; /* Adding null terminator */

    for (i = ZERO_INDEX; i < strlen(str); i++) /* Loop to go through all the chars in str */
        lowerCase_str[i] = (char) tolower(str[i]); /* Assigns the curr char as lower case */

    return lowerCase_str;
}

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2)
{
    return (str1 != NULL && str2 != NULL && strcmp(str1, str2) == SAME_STRINGS)? TRUE : FALSE;
}

/*
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
 * @return  The new created string str1 + str2, or NULL if str1 or str2 is NULL.
 */
char *connectTwoStrings(const char *str1, const char *str2)
{
    /* String to return */
    char *connectedString = NULL;

    if (str1 != NULL && str2 != NULL)
    {
        connectedString = (char *)
                allocate_space(strlen(str1) + strlen(str2) + SIZE_FOR_NULL);

        (void) strcpy(connectedString, str1); /* Appending str1 to the connected string */
        (void) strcat(connectedString, str2); /* Appending str2 */
    }

    return connectedString;
}

/*
 * Adds a given string to the first string.
 * Assumes that str1 and str2 are null-terminated, otherwise undefined behavior !
 * Basically does: str1 = str1 + str2.
 *
 * @param   **str1 Pointer to the first string.
 * @param   *str2 The string to add.
 */
void addTwoStrings(char **str1, const char *str2)
{
    /* If those pointers are NULL, we have nothing to do. */
    if (str1 != NULL && str2 != NULL)
    {
        if (*str1 == NULL) /* Create new space if the string is NULL */
        {
            *str1 = (char *) allocate_space(strlen(str2) + SIZE_FOR_NULL);
            *str1 = strcpy(*str1, str2); /* *str1 = str2 (str1 was empty before) */
        }
        else /* Add more space if the string already has some. */
        {
            *str1 = (char *) realloc(*str1,
                                     strlen(*str1) + strlen(str2) + SIZE_FOR_NULL);
            (void) strcat(*str1, str2); /* *str1 += str2 */
        }
    }
}

/*
 * Duplicates a given string.
 *
 * @param   str The input string to be duplicated.
 * @return      A pointer to the newly duplicated string if 'str' is not NULL.
 *              Returns NULL if 'str' is NULL.
 */
char *my_strdup(const char *str)
{
    char *dup_str = NULL; /* String to return. */

    if (str != NULL) /* Checking for invalid param. */
    {
        /* Duplicating the given string to a new one. */
        dup_str = (char *) allocate_space(strlen(str) + SIZE_FOR_NULL);
        dup_str = strncpy(dup_str, str, strlen(str) + SIZE_FOR_NULL);
    }

    return dup_str;
}

/*
 * Returns the index of a given string in an array of strings.
 *
 * @param   arr   The array of strings to search.
 * @param   size  The size of the array.
 * @param   str   The string to search for in the array.
 * @return  The index of an occurrence of the string in the array,
 *          or -1 if the string is not found.
 */
int getIndexOfStrInArray(const char *arr[], int size, const char *str)
{
    int i = size; /* Loop variable and index to return. */

    /* A loop that will stop until we find an element in arr that is equal to str, or i = -1. */
    while (--i >= ZERO_INDEX && sameStrings(arr[i], str) == FALSE);

    return i;
}

/*
 * Copies a part of a given string into a new one and returns it.
 *
 * @param   str     The given string to copy the part from.
 * @param   start   The start index of the part.
 * @param   end     The end index of the part.
 *
 * @return  The partial string: str[start...end] (null-terminated).
 */
char *strcpyPart(const char *str, int start, int end)
{
    int len = end - start; /* Length of the specific part. */

    /* Initializing the new part-string. */
    char *part = (char *) allocate_space(len + SIZE_FOR_NULL);
    part[len] = NULL_TERMINATOR;

    (void) strncpy(part, str + start, len); /* Copying the part from str the part. */

    return part;
}

/*
 * Gets a string containing the given value.
 *
 * @param   val     The number to make a string from.
 *
 * @return  The string containing the given value
 */
char *getStringFromVal(int val)
{
    int i; /* Loop variable. */
    int digitCnt = getDigitCnt(val);

    /* Create the string to return. */
    char *valStr = (char *) allocate_space(digitCnt + SIZE_FOR_NULL);
    valStr[digitCnt] = NULL_TERMINATOR; /* Add null terminator. */

    /* Add numbers to string from the right. */
    for (i = digitCnt - 1; i >= ZERO_INDEX; remove_right_digit(val), i++)
        valStr[i] = get_right_digit(val) + CHAR_ZERO;

    return valStr;
}

/*
 * Creates a start of line from a given string for a special format:
 * [word     ] (30) [tab] (1) [number] (as needed) [new line] (1)
 *
 * The start of line will be the [word    ] (30) [tab] (1) part of it,
 * means a word, spaces to cover 30 characters and a tab key.
 * assume the given string is of length of 30 or less (not NULL).
 *
 * @param   *str    The string to be the word in the format.
 *
 * @return  The first part of the format.
 */
char *createStartLineForFormat(const char *str)
{
    int i, len = (int) strlen(str); /* Loop variables. */

    char *newLine = (char *) allocate_space(SIZE_FOR_STR + SIZE_FOR_TAB + SIZE_FOR_NULL);
    newLine[SIZE_FOR_STR + SIZE_FOR_TAB] = NULL_TERMINATOR; /* Add null terminator. */

    (void) strcpy(newLine, str); /* Copy the string to the new line. */

    for (i = len; i < SIZE_FOR_STR; i++) /* Fill the rest with spaces */
        newLine[i] = SPACE_KEY;

    newLine[SIZE_FOR_STR] = TAB_KEY; /* Add a tab at the end. */

    return newLine;
}

/*
 * Creates a line from the special format:
 * [word     ] (30) [tab] (1) [number] (as needed) [new line] (1)
 * and appends it to the given pointer to string.
 *
 * @param   **pString   The pointer to the string to add the new line of special format to.
 * @param   *str        Holds the word of the special format.
 * @param   val         Holds the number of the special format.
 */
void addToStringInFormat(char **pString, const char *str, int val)
{
    /* Create helper strings. */
    char *startLine = createStartLineForFormat(str);
    char *valStr = getStringFromVal(val);
    char *endLine = getDynamicString("\n");

    /* Connect them the full line and add them. */
    addTwoStrings(&valStr, endLine);
    addTwoStrings(&startLine, valStr);
    addTwoStrings(pString, startLine);

    /* Free helper strings. */
    (void) free_ptr(POINTER(endLine));
    (void) free_ptr(POINTER(valStr));
    (void) free_ptr(POINTER(startLine));
}