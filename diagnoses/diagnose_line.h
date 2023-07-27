/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * */

#ifndef MMN_22_DIAGNOSE_INPUT_H
#define MMN_22_DIAGNOSE_INPUT_H

#include "../errors/error_types/error_types.h"
#include "../new-data-types/word_number.h"

/* ----------Prototypes---------- */

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

/* Given the param const char *command and the param Error error,
 * Returns a string contains a suggested fix for the error in the command. */
char *getCmdFix(const char *command, Error error);

/* Finds index of parameter in const char *line.
 * param paramNum specifies the number of parameter to seek.
 * This functions presumes that the command and the commas (up to the parameter to find)
 * are valid since it is supposed to be called after they are validated.
 * Returns the index of the wanted parameter or index of last char ('\0') in line if there isn't. */
int findParamIndex(const char *line, word_number paramNum);

/* Finds the length of the parameter number paramNum with type paramtype pType
 * in const char *line.
 * Returns the length of the specific parameter. */
int findParamLen(const char *line, word_number paramNum);// paramtype pType);

/* Gets the float parameter numbered paramNum from param const char *line.
 * Returns the specified float value. */
float getFloatParamFromLine(const char *line, word_number paramNum);

/* Gets the char parameter numbered paramNum from param const char *line.
 * Returns the specified char. */
char getCharParamFromLine(const char *line, word_number paramNum);

/* Checks if the line needs to be skipped.
 * param const char *line is the line to check
 * Return TRUE if the line needs to be skipped, otherwise FALSE. */
boolean isSkipLine(const char *line);

/* ------------------------------ */

#endif /* MMN_22_DIAGNOSE_INPUT_H */
