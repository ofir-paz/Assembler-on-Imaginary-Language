/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define MAX_SIZE 50
/* ------------ */

/* Data structure to hold the memory image. 2 represents the number of real bytes
 * needed to represent an imaginary byte. We do not use a final here for encapsulation. */
typedef struct
{
    char (*code)[2];
    char (*data)[2];
} MemoryImage;

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

void encodeLine(const char *line, MemoryImage *memoryImage, int transition, ...)
{

}

boolean isLineNeedEncode(const char *line)
{

}

void encodeCommand(const char *line)
{}