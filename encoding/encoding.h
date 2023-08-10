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

/*
 * Create a new MemoryImage structure.
 *
 * @return  A pointer to the newly created MemoryImage structure.
 */
MemoryImage *createMemoryImage(int IC, int DC);


/*
 * Encodes the given abstract syntax tree (AST) representing a line of assembly code
 * into the specified memory image, considering normal and external labels, and
 * external file contents.
 * Adds content to external file if needed !
 *
 * @param   *lineAst            Abstract syntax tree (AST) representing the line of assembly code.
 * @param   *memoryImage        The memory image where the encoded instructions/data will be stored.
 * @param   *normalLabels       The normal labels table.
 * @param   *extLabels          The external labels table.
 * @param   **extFileContents   A pointer to the string of the external file content to output.
 */
void encodeLine(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                NameTable *extLabels, char **extFileContents);

/* ---------------------------------------- */

#endif /* MMN_14_ENCODING_H */