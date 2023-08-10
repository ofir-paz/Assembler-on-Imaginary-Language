/*
 * @author Ofir Paz
 * @version (10/08/2023)
 *
 * Header file for the MemoryImage.c file.
 */

#ifndef MMN_14_MEMORYIMAGE_H
#define MMN_14_MEMORYIMAGE_H

#include "word.h"
#include "../../general-enums/assemblerFinals.h"

/* Data structure to hold the memory image. 2 represents the number of real bytes */
typedef struct
{
    word_t *instructions;
    word_t *data;
    int currWord[COUNTERS_AMOUNT];
} MemoryImage;

#endif /* MMN_14_MEMORYIMAGE_H */
