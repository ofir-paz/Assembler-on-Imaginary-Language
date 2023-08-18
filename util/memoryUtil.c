/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the function to assist with memory related functions.
 */

/* ---Include header files--- */
#include <stdlib.h>
#include "../errors/system_errors.h"
/* -------------------------- */

/* ---Finals--- */
#define WAS_NULL_RETURN_CODE (-1)
#define FREED_RETURN_CODE 0
/* ------------ */

/* ---Macros--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Gets a pointer with allocated space in the memory with the given size.
 * Terminates the program on allocation error !
 *
 * @param   size    The size of the pointer.
 *
 * @return  Allocated pointer with the given size.
 */
void *allocate_space(size_t size)
{
    void *ptr = malloc(size); /* Allocating the space */
    handle_allocation_error(ptr); /* Handling errors if there are */
    return ptr;
}

/*
 * Frees a given pointer.
 *
 * @param   *ptr    Pointer to free.
 *
 * @return  0 if the pointer was freed, (-1) if the pointer was already NULL.
 */
int free_ptr(void *ptr)
{
    int returnCode = WAS_NULL_RETURN_CODE; /* Assume the given pointer doesn't need to be free */

    if (ptr != NULL) /* Check if we were given a NULL pointer */
    {
        /* Free the pointer */
        free(ptr);
        returnCode = FREED_RETURN_CODE;
    }

    return returnCode;
}