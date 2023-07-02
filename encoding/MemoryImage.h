/*
 * @author Ofir Paz
 * @version (02/07/2023)
 *
 * This file contains the new data type 'MemoryImage'.
 */

#ifndef MMN_14_MEMORYIMAGE_H
#define MMN_14_MEMORYIMAGE_H

/* ---Finals--- */

/* Indicates how many real bytes we need to use to represent a word. */
#define REAL_BYTES_FOR_WORD 2

/* ------------ */

/* MemoryImage data type. */
typedef char (*MemoryImage)[REAL_BYTES_FOR_WORD];

#endif /* MMN_14_MEMORYIMAGE_H */
