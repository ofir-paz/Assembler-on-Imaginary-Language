/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the general_help_methods.c file.
 * */

#ifndef MMN_22_GENERAL_HELP_METHODS_H
#define MMN_22_GENERAL_HELP_METHODS_H

/* ---Macros--- */
#define POINTER(ptr) (void **)(ptr)
/* ------------ */

/* ---------------Prototypes--------------- */

/* Allocates space in the memory for a given pointer.
 * Terminates the program on allocation error !
 * param void *ptr is the pointer to allocate space for
 * param size_t size is the size of the space to allocate
 * Returns nothing. */
void allocate_space(void *ptr, size_t size);

/*
 * Frees a given pointer.
 *
 * @param **ptr Pointer to free.
 * @return 0 if the pointer was freed, (-1) if the pointer was already NULL.
 */
int free_ptr(void **ptr);

/* Turns every char in the given param char *str to lower case.
 * Returns the created lower case string */
char *strToLowerCase(const char *str);

/* Return TRUE if str1 == str2, otherwise FALSE. */
boolean sameStrings(const char *str1, const char *str2);

/*
 * Adds a given string to the first string.
 * Assumes that str1 and str2 are null-terminated, otherwise undefined behavior !
 * Basically does: str1 = str1 + str2.
 *
 * @param   **str1 The first string.
 * @param   *str2 The string to add.
 */
void addTwoStrings(char **str1, const char *str2);

/*
 * Connects two given strings to a new string.
 *
 * @param   *str1 The first string to connect.
 * @param   *str2 The second string to connect.
 * @return  The new created string str1 + str2.
 */
char *connectTwoStrings(const char *str1, const char *str2);

/* ---------------------------------------- */

#endif /* MMN_22_GENERAL_HELP_METHODS_H */