/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * */

#ifndef MMN_22_DIAGNOSE_INPUT_H
#define MMN_22_DIAGNOSE_INPUT_H

#include "../new-data-types/word_number.h"

/* ----------Prototypes---------- */

/* Finds a specified word in a given line string.
 * param const char *line is the line string that holds the word
 * param char **word is a pointer to the string that will hold the found word
 * param word_number wordNumber is the number of the word to seek, must be positive !
 * Returns nothing. */
void findWord(const char *line, char **word, word_number wordNumber);

/* Given the param const char *command and the param Error error,
 * Returns a string contains a suggested fix for the error in the command. */
char *getCmdFix(const char *command, Error error);

/* Finds index of parameter in const char *line.
 * param paramNum specifies the number of parameter to seek.
 * This functions presumes that the command and the commas (up to the parameter to find)
 * are valid since it is supposed to be called after they are validated.
 * Returns the index of the wanted parameter or index of last char ('\0') in line if there isn't. */
int findParamIndex(const char *line, ParamNum paramNum);

/* Finds the length of the parameter number paramNum with type paramtype pType
 * in const char *line.
 * Returns the length of the specific parameter. */
int findParamLen(const char *line, ParamNum paramNum, paramtype pType);

/* Gets the float parameter numbered paramNum from param const char *line.
 * Returns the specified float value. */
float getFloatParamFromLine(const char *line, ParamNum paramNum);

/* Gets the char parameter numbered paramNum from param const char *line.
 * Returns the specified char. */
char getCharParamFromLine(const char *line, ParamNum paramNum);

/* Checks if the line needs to be skipped.
 * param const char *line is the line to check
 * Return TRUE if the line needs to be skipped, otherwise FALSE. */
boolean isSkipLine(const char *line);

/* ------------------------------ */

#endif /* MMN_22_DIAGNOSE_INPUT_H */
