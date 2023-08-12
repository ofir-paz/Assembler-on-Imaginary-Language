/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 * 
 * Direction: 11  ---  9 || 8 -- 5 || 4   ---   2 || 1     0
 *            src method || opcode || dest method || A, R, E
 *            
 * Second word will be destination argument data (if instant) or address (if direct) + A, R, E.
 * Third word will be source argument + A, R, E.
 * 
 * If an argument is a register, the word saving it will be:
 *            11 -- 7 || 6  --  2 || 1     0
 *            src reg || dest reg || A, R, E
 * So if the source argument and the destination argument are registers,
 * only one extra word will be decoded.
 * 
 * Data:
 * 
 * For the .data guidance, the encoding will be an array of bits representing 
 * the numbers in the arguments without the A, R, E field.
 * 
 * For the .string guidance, the encoding will be an array of bits representing 
 * the characters in the string argument without the A, R, E + '\0' (word with all bits 0)
 * at the end.
 * 
 * Explanation about A, R, E fields:
 *      A: absolute encoding, independent of where the program will be loaded to the memory.
 *      R: relocatable encoding, dependant of where the program will be loaded to the memory.
 *      E: external encoding, dependant of a where something external (from a different file)
 *         will be loaded to the memory.
 */

/* ---Include header files--- */
#include <stdio.h>
#include <string.h>
#include "../new-data-types/boolean.h"
#include "../assembler_ast/assembler_ast.h"
#include "../NameTable/NameTable.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/neededKeys.h"
#include "../general-enums/indexes.h"
#include "../general-enums/assemblerFinals.h"
#include "encodingDataStructures/MemoryImage.h"
#include "encodingUtil.h"
#include "wordHandling.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define ZERO_BYTE 0
#define FULL_1_BYTE 0xff
#define BITS_IN_BYTE 8
#define START_WORD_RANGE 0
#define END_WORD_RANGE 11
#define CHARS_FOR_WORD 2
#define SIZE_FOR_NEW_LINE 1
#define FIRST_PART_OF_WORD 0
#define SECOND_PART_OF_WORD 1
#define BUFFER 82
/* ------------ */

/* ------------------------------------------ */

/* ---------------Prototypes--------------- */
void encodeInstruction(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents);
void encodeDataNumber(ast_t *lineAst, MemoryImage *memoryImage);
void encodeDataString(ast_t *lineAst, MemoryImage *memoryImage);
void encodeInstructionWithZeroArgs(word_t *instructions, int *currWord);
void encodeInstructionWithOneArgs(word_t *instructions, int *currWord, arg_node_t *argument,
                          NameTable *normalLabels, NameTable *extLabels, char **extFileContents);
void encodeInstructionWithTwoArgs(word_t *instructions, int *currWord, arg_node_t *firstArg,
                          arg_node_t *secondArg, NameTable *normalLabels, NameTable *extLabels,
                          char **extFileContents);
/* ---------------------------------------- */

/*
 * Create a new MemoryImage structure.
 *
 * @return  Pointer to the newly created MemoryImage structure.
 */
MemoryImage *createMemoryImage(int IC, int DC)
{
    MemoryImage *newMemoryImage = (MemoryImage *) allocate_space(sizeof(MemoryImage));

    /* Allocating space for the instructions memory image. */
    if(IC) newMemoryImage -> instructions = (word_t *) allocate_space(IC * sizeof(word_t));
    else newMemoryImage -> instructions = NULL;

    /* Allocating space for the data memory image. */
    if(DC) newMemoryImage -> data = (word_t *) allocate_space(DC * sizeof(word_t));
    else newMemoryImage -> data = NULL;

    /* Resetting values. */
    newMemoryImage -> currWord[IC_] = ZERO_INDEX;
    newMemoryImage -> currWord[DC_] = ZERO_INDEX;

    return newMemoryImage;
}

/*
 * Gets encoding information.
 * Encoding information is the following string: {IC [tab] DC [new line]}.
 *
 * @param   *memoryImage    The memory image with the encoding to get its information.
 */
char *getEncodingInformation(MemoryImage *memoryImage)
{
    /* Create info string, {IC [tab] DC} */
    char info[BUFFER];
    sprintf(info, "%d\t%d\n", memoryImage -> currWord[IC_], memoryImage -> currWord[DC_]);

    return getDynamicString(info);
}

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
 * @param   **extFileContents   Pointer to the string of the external file content to output.
 */
void encodeLine(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                NameTable *extLabels, char **extFileContents)
{
    sentence_t astSentence = getSentence(lineAst);

    if (astSentence.sentenceType == DIRECTION_SENTENCE) /* Encode direction. */
        encodeInstruction(lineAst, memoryImage, normalLabels, extLabels, extFileContents);

    /* lineAst.sentenceType == GUIDANCE_SENTENCE */
    else if (astSentence.sentence.guidance == data) /* Encode number data. */
        encodeDataNumber(lineAst, memoryImage);
    else if (astSentence.sentence.guidance == str) /* Encode string data. */
        encodeDataString(lineAst, memoryImage);
}

/*
 * Encodes the given abstract syntax tree (AST) representing an instruction
 * into the specified memory image, considering normal and external labels, and
 * external file contents.
 * Adds content to external file if needed !
 *
 * @param   *lineAst            The abstract syntax tree (AST) representing the instruction.
 * @param   *memoryImage        The memory image where the encoded instruction will be stored.
 * @param   *normalLabels       The normal labels table.
 * @param   *extLabels          The external labels table.
 * @param   **extFileContents   Pointer to the string of the external file content to output.
 */
void encodeInstruction(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents)
{
    /* Save instruction data image and current address to encode instruction in. */
    word_t *instructions = memoryImage -> instructions;
    int *currWord = memoryImage -> currWord + IC_;

    /* Save arguments (if there are). */
    arg_node_t *firstArg = getArgList(lineAst);
    arg_node_t *secondArg = (firstArg == NULL) ? NULL : getNextNode(firstArg);

    encodePartDir(instructions, *currWord, getSentence(lineAst).sentence.opcode);

    /* Encode instruction according to different cases of argument count. */
    if (firstArg == NULL)
        encodeInstructionWithZeroArgs(instructions, currWord);

    else if (secondArg == NULL)
        encodeInstructionWithOneArgs(instructions, currWord, firstArg,
                                     normalLabels, extLabels, extFileContents);
    else
        encodeInstructionWithTwoArgs(instructions, currWord, firstArg, secondArg, normalLabels,
                                     extLabels, extFileContents);
}

/*
 * Encodes the given abstract syntax tree (AST) representing a .data guidance.
 * into the specified memory image.
 *
 * @param   *lineAst        The abstract syntax tree (AST) representing the .data guidance.
 * @param   *memoryImage    The memory image where the encoded data will be stored.
 */
void encodeDataNumber(ast_t *lineAst, MemoryImage *memoryImage)
{
    arg_node_t *currArgument = getArgList(lineAst);

    while (currArgument != NULL) /* Go through all arguments and encode them. */
    {
        encodeDataVal(memoryImage -> data, memoryImage -> currWord[DC_],
                      getArgData(currArgument).data.num); /* Encode the number. */
        memoryImage -> currWord[DC_]++; /* Next word. */
        currArgument = getNextNode(currArgument); /* Next argument. */
    }
}

/*
 * Encodes the given abstract syntax tree (AST) representing a .string guidance
 * into the specified memory image.
 *
 * @param   *lineAst        The abstract syntax tree (AST) representing the .string guidance.
 * @param   *memoryImage    The memory image where the encoded data will be stored.
 */
void encodeDataString(ast_t *lineAst, MemoryImage *memoryImage)
{
    /* String to encode. */
    char *dataString = getArgData(getArgList(lineAst)).data.string;
    int i, stringLen = (int) strlen(dataString) - TWO_QUOTES; /* Loop variables. */

    /* Add every char in the string to the data image (ignore the " "). */
    for (i = ONE_INDEX; i < stringLen; i++, memoryImage -> currWord[DC_]++)
        encodeDataVal(memoryImage -> data, memoryImage -> currWord[DC_], dataString[i]);

    /* Add null terminator to end of string in data. */
    encodeDataVal(memoryImage -> data, memoryImage -> currWord[DC_], ZERO_BYTE);
}

/*
 * Encodes an instruction with zero arguments into the specified word.
 *
 * @param   *instructions   Array of words where the instruction will be encoded.
 * @param   *currWord       Pointer to the current word index in the array (updated after encoding).
 */
void encodeInstructionWithZeroArgs(word_t *instructions, int *currWord)
{
    /* Turn addressing methods for dest and src arguments to 0. */
    encodeAddressingMethods(instructions[*currWord],
                            ZERO_ADD_MTD, ZERO_ADD_MTD);
    (*currWord)++; /* Increase currWord by 1 since only 1 word is needed for decoding. */
}

/*
 * Encodes an instruction with one argument into the specified array of words.
 *
 * @param   *instructions       Array of words where the instruction will be encoded.
 * @param   *currWord           pointer to the current word index in the array
 *                              (updated after encoding).
 * @param   *argument           Argument node representing the argument of the instruction.
 * @param   *normalLabels       Table of normal labels for reference.
 * @param   *extLabels          Table of external labels for reference.
 * @param   **extFileContents   Pointer to the string of the external file content to output.
 */
void encodeInstructionWithOneArgs(word_t *instructions, int *currWord, arg_node_t *argument,
                          NameTable *normalLabels, NameTable *extLabels, char **extFileContents)
{
    addressing_method_t destMtd = getArgAddressingMethod(argument);
    encodeAddressingMethods(instructions[*currWord], destMtd, ZERO_ADD_MTD);

    (*currWord)++; /* Argument word */
    encodeDirArgument(instructions[*currWord], *currWord + PROGRAM_MEM_START, argument,
                      TRUE, normalLabels, extLabels, extFileContents);

    (*currWord)++; /* Next word */
}

/*
 * Encodes an instruction with one argument into the specified array of words.
 *
 * @param   *instructions       Array of words where the instruction will be encoded.
 * @param   *currWord           pointer to the current word index in the array
 *                              (updated after encoding).
 * @param   *firstArg           Argument node representing the first argument of the instruction.
 * @param   *secondArg          Argument node representing the second argument of the instruction.
 * @param   *normalLabels       Table of normal labels for reference.
 * @param   *extLabels          Table of external labels for reference.
 * @param   **extFileContents   pointer to the string of the external file content to output.
 */
void encodeInstructionWithTwoArgs(word_t *instructions, int *currWord, arg_node_t *firstArg,
                          arg_node_t *secondArg, NameTable *normalLabels, NameTable *extLabels,
                          char **extFileContents)
{
    /* Get addressing methods for both of the arguments and encode them into the first word. */
    addressing_method_t destMtd = getArgAddressingMethod(firstArg);
    addressing_method_t srcMtd = getArgAddressingMethod(secondArg);
    encodeAddressingMethods(instructions[*currWord], destMtd, srcMtd);

    (*currWord)++; /* First argument word. */

    /* Special case where both of the arguments are registers, they can be encoded in one word. */
    if (destMtd == DIRECT_REGISTER && srcMtd == DIRECT_REGISTER)
        encodeDirectRegisterArg(instructions[*currWord], getArgData(firstArg).data.reg,
                                getArgData(secondArg).data.reg);
    else /* Encode each argument to a different word (dest first). */
    {
        encodeDirArgument(instructions[*currWord], *currWord + PROGRAM_MEM_START, firstArg,
                          TRUE, normalLabels, extLabels, extFileContents);
        (*currWord)++; /* Second argument word. */
        encodeDirArgument(instructions[*currWord], *currWord + PROGRAM_MEM_START, secondArg,
                          FALSE, normalLabels, extLabels, extFileContents);
        (*currWord)++; /* Next instruction. */
    }
}

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
char *getEncodedWords(MemoryImage *memoryImage, boolean isWordsInstructions)
{
    int i; /* Loop variable. */
    word_t tmpWord; /* Temporary word to hold encoded Base64 words. */

    int wordsCnt = (isWordsInstructions)? memoryImage -> currWord[IC_] :
            memoryImage -> currWord[DC_]; /* How many words to encode. */
    int size = (CHARS_FOR_WORD + SIZE_FOR_NEW_LINE) * wordsCnt; /* Size of the string. */

    char *encoded64Words = (char *) allocate_space(size + SIZE_FOR_NULL);
    encoded64Words[size] = NULL_TERMINATOR; /* String to return. */

    /* Convert each word to Base64 and add a new line after it. */
    for (i = ZERO_INDEX; i < size; i += (CHARS_FOR_WORD + SIZE_FOR_NEW_LINE))
    {
        convertWordToBase64(memoryImage -> instructions[i], tmpWord);
        encoded64Words[i + FIRST_PART_OF_WORD] = (char) tmpWord[FIRST_PART_OF_WORD];
        encoded64Words[i + SECOND_PART_OF_WORD] = (char) tmpWord[SECOND_PART_OF_WORD];
        encoded64Words[i + CHARS_FOR_WORD] = ENTER_KEY;
    }

    return encoded64Words;
}

/*
 * Clears the memory image.
 *
 * @param   **pMemoryImage  Pointer to the memory image to clear.
 */
void clearMemoryImage(MemoryImage **pMemoryImage)
{
    (void) free_ptr(POINTER((*pMemoryImage) -> instructions));
    (void) free_ptr(POINTER((*pMemoryImage) -> data));
    (void) free_ptr(POINTER(*pMemoryImage));
}