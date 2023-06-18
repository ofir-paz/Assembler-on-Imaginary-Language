/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Includes--- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "general-enums//neededKeys.h"
#include "errors/system_errors.h"
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

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2)
{
    return (strcmp(str1, str2) == SAME_STRINGS)? TRUE : FALSE;
}

char *connectTwoStrings(const char *str1, const char *str2)
{
    char *connectedString = (char *) malloc(strlen(str1) + strlen(str2) + 1);
    handle_allocation_error(connectedString);
    strcpy(connectedString, str1);
    connectedString = strcat(connectedString, str2);
    return connectedString;
}
