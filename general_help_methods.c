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
#define POINTER(ptr) (void **)(&ptr)
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
void *allocate_space(size_t size)
{
    void *ptr = malloc(size); /* Allocating the space */
    handle_allocation_error(ptr); /* Handling errors if there are */
    return ptr;
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

/*
 * Creates a dynamically allocated string from a given string.
 *
 * @param   *str The string to recreate dynamically.
 * @return  The newly dynamically created string with the contents of str.
 */
char *getDynamicString(char *str)
{
    char *dynamicString = (char *) allocate_space(strlen(str));
    dynamicString = strcpy(dynamicString, str);
    return dynamicString;
}

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str)
{
    int i; /* Loop variable */
    
    /* Assigning space in the memory for the new string */
    char *lowerCase_str = (char *) allocate_space(strlen(str) + SIZE_FOR_NULL);

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
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
 * @return  The new created string str1 + str2, or NULL if str1 or str2 is NULL.
 */
char *connectTwoStrings(const char *str1, const char *str2)
{
    /* String to return */
    char *connectedString = NULL;

    if (str1 != NULL && str2 != NULL)
    {
        connectedString = (char *)
                allocate_space(strlen(str1) + strlen(str2) + SIZE_FOR_NULL);

        (void) strcpy(connectedString, str1); /* Appending str1 to the connected string */
        (void) strcat(connectedString, str2); /* Appending str2 */
    }

    return connectedString;
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
    if (str1 != NULL && str2 != NULL)
    {
        if (*str1 == NULL)
        {
            *str1 = (char *) allocate_space(strlen(str2));
            *str1 = strcpy(*str1, str2);
        }
        else
        {
            char *sumOfStrings = connectTwoStrings(*str1, str2);
            free_ptr(POINTER(*str1));
            *str1 = sumOfStrings;
        }
    }
}
