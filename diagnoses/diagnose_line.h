/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the diagnose_line.c file.
 */

#ifndef MMN_22_DIAGNOSE_INPUT_H
#define MMN_22_DIAGNOSE_INPUT_H

/* Include very basic data types. */
#include "../new-data-types/word_number.h"

/* ---------------Prototypes--------------- */

/* ---Data types prototypes--- */
typedef int Error;
/* --------------------------- */

/*
 * Finds the specified word in the given line and stores it in the provided pointer.
 *
 * @param   line        The input line containing words separated by spaces.
 * @param   word        A pointer to a char pointer that will store the found word.
 * @param   wordNumber  The position of the word to be extracted (0-indexed).
 *                      If wordNumber is negative or greater than the number of words in the line,
 *                      *word will be set to NULL.
 */
void findWord(const char *line, char **word, word_number wordNumber);

/*
 * Checks if the line needs to be skipped.
 *
 * @param   *line The line to check if it needs to be skipped.
 *
 * Return TRUE if the line needs to be skipped, otherwise FALSE.
 */
boolean isSkipLine(const char *line);

/*
 * Checks if the given string represents a valid integer.
 * Note: the integer can start with a plus or minus sign.
 *
 * @param   *str    The string to check for integer representation.
 *
 * @return  TRUE if the given string represents a valid integer, otherwise FALSE.
 */
boolean isStrInteger(const char *str);

/*
 * Checks if the given string represents a valid floating-point number.
 *
 * @param   *str    The string to check for floating-point representation.
 *
 * @return  TRUE if the given string represents a valid floating-point number, otherwise FALSE.
 */
boolean isStrFloat(const char *str);

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
boolean isCharAfterCommas(const char *line, int commaIndex);

/*
 * Checks if the given string contains only printable characters.
 *
 * @param   *str    The string to check for printable characters.
 *
 * @return  TRUE if the given string contains only printable characters, otherwise FALSE.
 */
boolean isPrintable(const char *str);

/* ---------------------------------------- */

#endif /* MMN_22_DIAGNOSE_INPUT_H */
