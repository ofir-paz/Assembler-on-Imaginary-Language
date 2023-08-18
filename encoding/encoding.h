/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the encode-line.c file.
 */

#ifndef MMN_14_ENCODING_H
#define MMN_14_ENCODING_H

/* Prototype for data structure to hold the memory image. */
typedef struct MemoryImage MemoryImage;

/* ---------------Prototypes--------------- */

/*
 * Gets encoding information.
 * Encoding information is the following string: {IC [tab] DC [new line]}.
 *
 * @param   *memoryImage    The memory image with the encoding to get its information.
 */
MemoryImage *createMemoryImage(int IC, int DC);

/*
 * Gets encoding information.
 * Encoding information is the following string: {IC [tab] DC [new line]}.
 *
 * @param   *memoryImage    The memory image with the encoding to get its information.
 */
char *getEncodingInformation(MemoryImage *memoryImage);

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

/*
 * Gets a string representing the encoded words of the memory image in Base64.
 *
 * @param   *memoryImage            The memory image that holds the words to get the
 *                                  string representing them.
 * @param   isWordsInstructions     Flag indicating if the words to get the string
 *                                  from are instruction words or data words.
 *
 * @return  The string representing the specific encoded words of the memory image in Base64.
 */
char *getEncodedWords(MemoryImage *memoryImage, boolean isWordsInstructions);

/*
 * Clears the memory image.
 *
 * @param   **pMemoryImage  Pointer to the memory image to clear.
 */
void clearMemoryImage(MemoryImage **pMemoryImage);

/*
 ---DEBUGGING---IGNORE--- !!

void printMemImage(MemoryImage *memoryImage);
*/

/* ---------------------------------------- */

#endif /* MMN_14_ENCODING_H */