/*
 * @author Ofir Paz
 * @version (18/08/2023)
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
 * Gets a pointer with allocated space in the memory with the given size.
 * Terminates the program on allocation error !
 *
 * @param   size    The size of the pointer.
 *
 * @return  Allocated pointer with the given size.
 */
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
