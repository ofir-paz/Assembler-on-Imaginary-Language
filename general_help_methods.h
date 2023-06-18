/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the help_methods.c file.
 * */

#ifndef MMN_22_HELP_METHODS_H
#define MMN_22_HELP_METHODS_H

#include "new-data-types/boolean.h"

/* ----------Prototypes---------- */

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str);

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2);

char *connectTwoStrings(const char *str1, const char *str2);
/* ------------------------------ */

#endif /* MMN_22_HELP_METHODS_H */
