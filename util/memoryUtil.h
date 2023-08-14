/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * Header file for the memoryUtil.c file.
 */

#ifndef MMN_14_MEMORYUTIL_H
#define MMN_14_MEMORYUTIL_H

/* ---Macros--- */
#define clear_ptr(ptr) free_ptr((ptr)); ptr = NULL;
/* ------------ */

/* ---------------Prototypes--------------- */

/*
 * Allocates space in the memory for a given pointer.
 * Terminates the program on allocation error !
 *
 * @param   *ptr    The pointer to allocate space for
 * param size_t size is the size of the space to allocate
 * Returns nothing. */
void *allocate_space(size_t size);

/*
 * Frees a given pointer.
 *
 * @param   *ptr    Pointer to free.
 *
 * @return  0 if the pointer was freed, (-1) if the pointer was already NULL.
 */
int free_ptr(void *ptr);

/* ---------------------------------------- */

#endif /* MMN_14_MEMORYUTIL_H */
