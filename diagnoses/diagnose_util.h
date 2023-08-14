/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the help_methods.c file.
 * */

#ifndef MMN_22_HELP_METHODS_H
#define MMN_22_HELP_METHODS_H

#include "../new-data-types/boolean.h"
#include "../new-data-types/word_number.h"

/* ----------Prototypes---------- */

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
void findTokenFromStr(const char *str, char **token, word_number tokenNumber, const char *delim);

/* Checks if the param int i is an index of param const char *str.
 * Returns TRUE if i is an index of the given string, otherwise FALSE. */
boolean isIndexInStr(const char *str, int i);

/* Returns TRUE if param char ch is empty (space; tab; enter), otherwise FALSE */
boolean isEmpty(char ch);

/* Finds the next index in param const char *str where it is not an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next non-empty space in str (index of null if there isn't). */
int nextCharIndex(const char *str, int i);

/* Finds the next index in param const char *str where it is an empty space (tab/space/enter).
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next empty space in str (index of null if there isn't) */
int nextEmptyIndex(const char *str, int i);

/*
 * Finds the next index in the given string which points to a different word.
 * If the given index is any negative value, returns the first word index.
 * If it's after the last char in the given string, returns the given index.
 *
 * @param   *str The line string.
 * @param   i The given index.
 * @return  The next word index from i in str, or i if i > len(str).
 */
int nextWordIndex(const char *str, int i);

/* Finds the next index in param const char *str where it is the given char ch.
 * If param int i is not an index of str returns i,
 * otherwise returns the index of the next ch in str or (index of null if there isn't) */
int nextSpecificCharIndex(const char *str, int i, char ch);

/* Finds the start of a specific word in a given line string.
 * param const char *line is the line that holds the word
 * param word_number wordNumber is the number of the word to find its start index
 * Returns the found start index of the specific word in line. */
int findStartIndexOfWord(const char *line, word_number wordNumber);

/* Gets the next non-empty char from a given index in a given string.
 * param const char *str is the string to seek for the next char in
 * param int i is the index to start the search from
 * Returns the next non-empty char, or 0 ('\0') if there isn't. */
char getNextChar(const char *str, int i);

/* Returns TRUE if const char ch = '+' or '-', otherwise FALSE. */
boolean isPlusOrMinus(char ch);

/* Counts the dots in param const char *str from index
 * int start to index int end.
 * Return the amount of found dots. */
int countDots(const char *str, int start, int end);

/*
 * Checks if a given char is an english letter.
 *
 * @param   ch  The char to check if it's a letter.
 *
 * @return  TRUE if ch is a letter, otherwise FALSE.
 */
boolean isLetter(char ch);

/* Returns TRUE if the char in index int index of param const char *str
 * is a comma, otherwise FALSE. */
boolean isCurrCharComma(const char *str, int index);

/* Returns TRUE if the param char ch is a number, otherwise FALSE. */
boolean isCharNumber(char ch);

/*
 * Checks if a given char is a legal character (letter or number).
 *
 * @param   ch  The given character to check if it's a legal character.
 *
 * @return  TRUE if ch is a legal character, otherwise FALSE.
 */
boolean isLegalChar(char ch);

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
