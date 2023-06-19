/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Includes--- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "new-data-types/boolean.h"
#include "general-enums/neededKeys.h"
#include "errors/system_errors.h"
/* -------------- */

/* ---Finals--- */
#define SAME_STRINGS 0
#define ZERO_INDEX 0
#define SIZE_FOR_NULL 1
/* ------------ */

/* Allocates space in the memory for a given pointer.
 * Terminates the program on allocation error !
 * param void *ptr is the pointer to allocate space for
 * param size_t size is the size of the space to allocate
 * Returns nothing. */
void allocate_space(void *ptr, size_t size)
{
    ptr = (typeof(ptr)) malloc(size); /* Allocating the space */
    handle_allocation_error(ptr); /* Handling errors if there are */
}

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str)
{
    int i; /* Loop variable */
    
    /* Assigning space in the memory for the new string */
    char *lowerCase_str;
    allocate_space(lowerCase_str, strlen(str) + SIZE_FOR_NULL);

    lowerCase_str[strlen(str)] = NULL_TERMINATOR; /* Adding null terminator */

    for (i = ZERO_INDEX; i < strlen(str); i++) /* Loop to go through all the chars in str */
        lowerCase_str[i] = (char) tolower(str[i]); /* Assigns the curr char as lower case */

    return lowerCase_str;
}

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2)
{
    return (strcmp(str1, str2) == SAME_STRINGS)? TRUE : FALSE;
}

/* Connects two given strings to a new string.
 * param const char *str1 is the first string to connect
 * param const char *str2 is the second string to connect
 * Returns the new created string str1 + str2. */
char *connectTwoStrings(const char *str1, const char *str2)
{
    char *connectedString; /* String the return */
    allocate_space(connectedString, strlen(str1) + strlen(str2) + SIZE_FOR_NULL);

    strcpy(connectedString, str1); /* Appending str1 to the connected string */
    connectedString = strcat(connectedString, str2); /* Appending str2 */

    return connectedString;
}
