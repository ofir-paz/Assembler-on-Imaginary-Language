/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * Header file for the encode-line.c file.
 */

#ifndef MMN_14_ENCODING_H
#define MMN_14_ENCODING_H

/* Prototype for data structure to hold the memory image. */
typedef struct MemoryImage MemoryImage;

/* ---------------Prototypes--------------- */
void encodeLine(const char *line, MemoryImage *memoryImage, int transition, ...);
/* ---------------------------------------- */

#endif /* MMN_14_ENCODING_H */