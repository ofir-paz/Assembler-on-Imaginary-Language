/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the help_methods.c file.
 * */

#ifndef MMN_22_HELP_METHODS_H
#define MMN_22_HELP_METHODS_H

#include "../new-data-types/boolean.h"

/* ----------Prototypes---------- */

/* Checks if the param int i is an index of param const char *str.
 * Returns TRUE if i is an index of the given string, otherwise FALSE. */
boolean isIndexInStr(const char *str, int i);

/* Finds the next index in param const char *str where it is not an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next non-empty space in str (index of null if there isn't). */
int nextCharIndex(const char *str, int i);

/* Finds the next index in param const char *str where it is an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next empty space in str (index of null if there isn't) */
int nextEmptyIndex(const char *str, int i);

/* Finds the next index in param const char *str which points to a different word.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next word in str (index of null if there isn't) */
int nextWordIndex(const char *str, int i);

/* Finds the next index in param const char *str where it is a comma.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next comma in str (index of null if there isn't) */
int nextCommaIndex(const char *str, int i);

/* Returns TRUE if const char ch = '+' or '-', otherwise FALSE. */
boolean isPlusOrMinus(char ch);

/* Counts the dots in param const char *str from index
 * int start to index int end.
 * Return the amount of found dots. */
int countDots(const char *str, int start, int end);

/* Returns TRUE if the char in index int index of param const char *str
 * is a comma, otherwise FALSE. */
boolean isCurrCharComma(const char *str, int index);

/* Returns TRUE if the char in index int index of param const char *str
 * is a number, otherwise FALSE. */
boolean isCurrCharNumber(const char *str, int index);

/* Returns TRUE if the char in index int index of param const char *str
 * is a dot, otherwise FALSE. */
boolean isCurrCharDot(const char *str, int index);

/* Returns TRUE if the char in param const char *str at index param int index is an
 * element of a number (+; -; .; 0-9), otherwise FALSE. */
boolean isPartOfNumber(const char *str, int index);

/* Searches for the next empty space or comma in param const char *str
 * from the starting index param in index.
 * Return the index of the found empty space or comma, or end index of str if there are not. */
int nextEmptyCommaIndex(const char *str, int index);

/* ------------------------------ */

#endif /* MMN_22_HELP_METHODS_H */
