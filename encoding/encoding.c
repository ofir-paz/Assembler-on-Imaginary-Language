/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "assembler_ast.h"
#include "../util/memoryUtil.h"
/* -------------------------- */

/* ---Macros--- */
#define FIRST_N_BITS(byte, n) ((byte) & (0xff >> (BITS_IN_BYTE - (n))))
#define LAST_N_BITS(byte, n) ((byte) & (0xff << (BITS_IN_BYTE - (n))))
/* ------------ */

/* ---Finals--- */
#define BITS_IN_BYTE 8
#define BYTES_FOR_WORD 2
#define MAX_SIZE 60
#define ADD_SIZE 30
#define FIRST_PART_OF_WORD 0
#define SECOND_PART_OF_WORD 1
#define SIX_NUMBER 6
#define TWO_NUMBER 2
#define FOUR_NUMBER 4
/* ------------ */

/* Data structure to hold the memory image. 2 represents the number of real bytes */
typedef struct
{
    unsigned char (*instructions)[BYTES_FOR_WORD];
    unsigned char (*data)[BYTES_FOR_WORD];
} MemoryImage;

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Create a new MemoryImage structure.
 *
 * @return  A pointer to the newly created MemoryImage structure.
 */
MemoryImage *createMemoryImage()
{
    MemoryImage *newMemoryImage = (MemoryImage *) allocate_space(sizeof(MemoryImage));

    /* Allocating space for the instructions memory image. */
    newMemoryImage -> instructions = (unsigned char (*)[BYTES_FOR_WORD])
            allocate_space(MAX_SIZE * BYTES_FOR_WORD);

    /* Allocating space for the data memory image. */
    newMemoryImage -> data = (unsigned char (*)[BYTES_FOR_WORD])
            allocate_space(MAX_SIZE * BYTES_FOR_WORD);

    return newMemoryImage;
}

void encodeLine(const ast_t *lineAst, MemoryImage *memoryImage)
{

}

void encodeCommand(const char *line)
{

}

/*
 * Convert a word to a Base64 representation.
 *
 * @param   word    The word to be converted.
 */
void convertWordToBase64(unsigned char word[BYTES_FOR_WORD])
{
    /* Since a word in the assembly language requires a minimum
     * of two bytes to be represented, We take the first 6 bits of the
     * representation, and the last 6 bits of it and convert them. */
    char firstChar = FIRST_N_BITS(word[FIRST_PART_OF_WORD], SIX_NUMBER); /* Take first 6. */
    char secondChar = LAST_N_BITS(word[FIRST_PART_OF_WORD], TWO_NUMBER) |
                      FIRST_N_BITS(word[SECOND_PART_OF_WORD], FOUR_NUMBER); /* Take last 6. */

    /* Assign them back to the word. */
    word[FIRST_PART_OF_WORD] = firstChar;
    word[SECOND_PART_OF_WORD] = secondChar;
}