/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the stringsUtil.c file.
 */

#ifndef MMN_14_STRINGSUTIL_H
#define MMN_14_STRINGSUTIL_H

#include "../new-data-types/boolean.h"

/* ---------------Prototypes--------------- */

/*
 * Creates a dynamically allocated string from a given string.
 *
 * @param   *str The string to recreate dynamically.
 * @return  The newly dynamically created string with the contents of str.
 */
char *getDynamicString(const char *str);

/*
 * Create a string with every char in the given string in lower case.
 *
 * @param   *str    The string to copy to lower case.
 *
 * @return  The created lower case string.
 */
char *strToLowerCase(const char *str);

/*
 * Checks if two given strings are the same.
 *
 * @param   *str1   The first string.
 * @param   *str2   The second string.
 *
 * @return  TRUE if str1 == str2, otherwise FALSE.
 */
boolean sameStrings(const char *str1, const char *str2);

/*
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
 *
 * @return  The new created string str1 + str2, or NULL if str1 or str2 is NULL.
 */
char *connectTwoStrings(const char *str1, const char *str2);

/*
 * Adds a given string to the first string.
 * Assumes that str1 and str2 are null-terminated, otherwise undefined behavior !
 * Basically does: str1 = str1 + str2.
 *
 * @param   **str1 Pointer to the first string.
 * @param   *str2 The string to add.
 */
void addTwoStrings(char **str1, const char *str2);

/*
 * Duplicates a given string.
 *
 * @param   str The input string to be duplicated.
 *
 * @return  A pointer to the newly duplicated string if 'str' is not NULL.
 *          Returns NULL if 'str' is NULL.
 */
char *my_strdup(const char *str);

/*
 * Returns the index of a given string in an array of strings.
 *
 * @param   arr   The array of strings to search.
 * @param   size  The size of the array.
 * @param   str   The string to search for in the array.
 *
 * @return  The index of an occurrence of the string in the array,
 *          or -1 if the string is not found.
 */
int getIndexOfStrInArray(const char *arr[], int size, const char *str);

/*
 * Copies a part of a given string into a new one and returns it.
 *
 * @param   str     The given string to copy the part from.
 * @param   start   The start index of the part.
 * @param   end     The end index of the part (not including end).
 *
 * @return  The partial string: str[start...end - 1] (null-terminated).
 */
char *strcpyPart(const char *str, int start, int end);

/*
 * Gets a string containing the given value.
 *
 * @param   val     The number to make a string from.
 *
 * @return  The string containing the given value
 */
char *getStringFromVal(int val);

/*
 * Creates a line from the special format:
 * [word     ] (30) [tab] (1) [number] (as needed) [new line] (1)
 * and appends it to the given pointer to string.
 *
 * @param   **pString   The pointer to the string to add the new line of special format to.
 * @param   *str        Holds the word of the special format.
 * @param   val         Holds the number of the special format.
 */
void addToStringInFormat(char **pString, const char *str, int val);

/* ---------------------------------------- */

#endif /* MMN_14_STRINGSUTIL_H */
