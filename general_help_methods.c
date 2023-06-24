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
#include "general-enums/indexes.h"
#include "general-enums/neededKeys.h"
#include "errors/system_errors.h"
/* -------------- */

/* ---Macros--- */
#define POINTER(ptr) (void **)(ptr)
/* ------------ */

/* ---Finals--- */
#define WAS_NULL_RETURN_CODE (-1)
#define FREED_RETURN_CODE 0
#define SIZE_FOR_NULL 1
#define ZERO_LENGTH 0
#define SAME_STRINGS 0
/* ------------ */

/* Allocates space in the memory for a given pointer.
 * Terminates the program on allocation error !
 * param void *ptr is the pointer to allocate space for
 * param size_t size is the size of the space to allocate
 * Returns nothing. */
void allocate_space(void **ptr, size_t size)
{
    *ptr = (typeof(*ptr)) malloc(size); /* Allocating the space */
    handle_allocation_error(ptr); /* Handling errors if there are */
}

/*
 * Frees a given pointer.
 *
 * @param **ptr Pointer to free.
 * @return 0 if the pointer was freed, (-1) if the pointer was already NULL.
 */
int free_ptr(void **ptr)
{
    int returnCode = WAS_NULL_RETURN_CODE; /* Assume the given pointer doesn't need to be free */

    if (ptr != NULL && *ptr != NULL) /* Check if we were given a NULL pointer */
    {
        /* Free the pointer */
        free(*ptr);
        *ptr = NULL;
        returnCode = FREED_RETURN_CODE;
    }

    return returnCode;
}

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str)
{
    int i; /* Loop variable */
    
    /* Assigning space in the memory for the new string */
    char *lowerCase_str;
    allocate_space(POINTER(lowerCase_str), strlen(str) + SIZE_FOR_NULL);

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

/*
 * Adds a given string to the first string.
 * Assumes that str1 and str2 are null-terminated, otherwise undefined behavior !
 * Basically does: str1 = str1 + str2.
 *
 * @param   **str1 The first string.
 * @param   *str2 The string to add.
 */
void addTwoStrings(char **str1, const char *str2)
{
    /* If those pointers are NULL, we have nothing to do. */
    if (str1 == NULL || str2 == NULL);

    else /* None of the pointers are NULL. */
    {
        size_t len1 = (*str1 == NULL)? ZERO_LENGTH : strlen(*str1);
        size_t len2 = strlen(str2);
        /* Allocates more space in the memory for str1 */
        *str1 = realloc(*str1, len1 + len2 + SIZE_FOR_NULL);
        handle_allocation_error(*str1);

        (void) strcat(*str1, str2); /* Adds the strings */
    }
}

/*
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
 * @return  The new created string str1 + str2.
 */
char *connectTwoStrings(const char *str1, const char *str2)
{
    char *connectedString; /* String the return */
    allocate_space(POINTER(connectedString),
                   strlen(str1) + strlen(str2) + SIZE_FOR_NULL);

    (void) strcpy(connectedString, str1); /* Appending str1 to the connected string */
    (void) strcat(connectedString, str2); /* Appending str2 */

    return connectedString;
}
