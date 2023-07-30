/*
 * @author Ofir Paz
 * @version (29/07/2023)
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
char *getDynamicString(char *str);

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str);

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2);

/*
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
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
 * @return  The index of an occurrence of the string in the array,
 *          or -1 if the string is not found.
 */
int getIndexOfStrInArray(const char *arr[], int size, const char *str);

/* ---------------------------------------- */

#endif /* MMN_14_STRINGSUTIL_H */
