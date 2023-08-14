/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdlib.h>
#include "../errors/system_errors.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define WAS_NULL_RETURN_CODE (-1)
#define FREED_RETURN_CODE 0
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Allocates space in the memory for a given pointer.
 * Terminates the program on allocation error !
 *
 * @param   *ptr    The pointer to allocate space for
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