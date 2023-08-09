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
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "assembler_ast.h"
#include "../NameTable/NameTable.h"
#include "../general-enums/indexes.h"
#include "../general-enums/assemblerFinals.h"
#include "../util/memoryUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define ZERO_BYTE 0
#define BYTES_FOR_WORD 2
#define FULL_1_BYTE 0xff
#define BITS_IN_BYTE 8
#define START_WORD_RANGE 0
#define END_WORD_RANGE 11

/* Ranges, as defined and explained in this file's description. */
enum {OPCODE_LOW = 5, OPCODE_HIGH = 8, ARG_LOW = 2, ARG_HIGH = 11,
        DEST_MTD_LOW = 2, DEST_MTD_HIGH = 4, SRC_MTD_LOW, SRC_MTD_HIGH,
        DEST_REG_LOW = 2, DEST_REG_HIGH = 6, SRC_REG_LOW = 7, SRC_REG_HIGH = 11,
        DIR_DATA_LOW = 2, DIR_DATA_HIGH = 11,
        ARE_LOW = 0, ARE_HIGH = 1,
        DATA_LOW = 0, DATA_HIGH = 11};
/* ------------ */

/* ---------------Memory Image--------------- */

typedef unsigned char word_t[BYTES_FOR_WORD];

/* Data structure to hold the memory image. 2 represents the number of real bytes */
typedef struct
{
    word_t *instructions;
    int currInstruction;
    word_t *data;
    int currData;
} MemoryImage;

/* ------------------------------------------ */

/* ---------------Prototypes--------------- */
void encodeDirection(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents);
void encodePartDir(word_t *instructions, int currWord, opcodes_t opcode);
void encodeDirWithZeroArgs(word_t *instructions, int *currWord);
void encodeDirWithOneArgs(word_t *instructions, int *currWord, arg_node_t *firstArg,
                          NameTable *normalLabels, NameTable *extLabels, char **extFileContents);
void encodeInstantArg(word_t word, int instantVal);
void encodeDirectArg(word_t word, const char *directLabel, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents, int address);
void encodeDirectRegisterArg(word_t word, register_t aRegister, boolean isDest);
void encodeToWordARE(word_t word, encoding_type_t encodingType);
/* ---------------------------------------- */

/*
 * Create a new MemoryImage structure.
 *
 * @return  A pointer to the newly created MemoryImage structure.
 */
MemoryImage *createMemoryImage(int IC, int DC)
{
    MemoryImage *newMemoryImage = (MemoryImage *) allocate_space(sizeof(MemoryImage));

    /* Allocating space for the instructions memory image. */
    newMemoryImage -> instructions = (word_t *) allocate_space(IC * sizeof(word_t));

    /* Allocating space for the data memory image. */
    newMemoryImage -> data = (word_t *) allocate_space(DC * sizeof(word_t));

    /* Resetting values. */
    newMemoryImage -> currInstruction = newMemoryImage -> currData = PROGRAM_MEM_START;

    return newMemoryImage;
}

void encodeLine(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                NameTable *extLabels, char **extFileContents)
{
    sentence_t astSentence = getSentence(lineAst);
    if (astSentence.sentenceType == DIRECTION_SENTENCE)
        encodeDirection(lineAst, memoryImage, normalLabels, extLabels, extFileContents);

        /* lineAst.sentenceType == GUIDANCE_SENTENCE */
    else if (astSentence.sentence.guidance == data)
        encodeData(lineAst, memoryImage->data);
    else if (astSentence.sentence.guidance == str)
        encodeString(lineAst, memoryImage->data);
}

void encodeDirection(ast_t *lineAst, MemoryImage *memoryImage, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents)
{
    word_t *instructions = memoryImage -> instructions;
    int currWord = memoryImage -> currInstruction;
    arg_node_t *firstArg = getArgList(lineAst);
    arg_node_t *secondArg = (firstArg == NULL) ? NULL : getNextNode(firstArg);

    encodePartDir(instructions, currWord, getSentence(lineAst).sentence.opcode);

    if (firstArg == NULL)
        encodeDirWithZeroArgs(instructions, &currWord);

    else if (secondArg == NULL)
        encodeDirWithOneArgs(instructions, &currWord, firstArg, normalLabels, extLabels,
                             extFileContents);
    else
        encodeDirWithTwoArgs(instructions, &currWord, firstArg, secondArg, normalLabels,
                             extLabels, extFileContents);
}

void encodePartDir(word_t *instructions, int currWord, opcodes_t opcode)
{
    /* Encode opcode. */
    setBitsInRangeToVal(instructions[currWord], OPCODE_LOW, OPCODE_HIGH,opcode);
    /* Encode known A, R, E field (instruction is always absolute). */
    encodeToWordARE(instructions[currWord], ABSOLUTE);
}

void encodeDirWithZeroArgs(word_t *instructions, int *currWord)
{
    /* Turn addressing methods for dest and src arguments to 0. */
    setBitsInRangeToVal(instructions[*currWord],
                        DEST_MTD_LOW, DEST_MTD_HIGH, ZERO_BYTE);
    setBitsInRangeToVal(instructions[*currWord],
                        SRC_MTD_LOW, SRC_MTD_HIGH, ZERO_BYTE);
    (*currWord)++; /* Increase currWord by 1 since only 1 word is needed for decoding. */
}

void encodeDirWithOneArgs(word_t *instructions, int *currWord, arg_node_t *firstArg,
                          NameTable *normalLabels, NameTable *extLabels, char **extFileContents)
{
    addressing_method_t arg1mtd = getArgAddressingMethod(firstArg);
    setBitsInRangeToVal(instructions[*currWord], DEST_MTD_LOW, DEST_MTD_HIGH,
                        arg1mtd);
    setBitsInRangeToVal(instructions[*currWord], SRC_MTD_LOW, SRC_MTD_HIGH,
                        ZERO_BYTE);

    switch (arg1mtd)
    {
        case INSTANT: /* Encode single instant value argument. */
            encodeInstantArg(instructions[*currWord + 1],
                             getArgData(firstArg).data.num);
            break;
        case DIRECT: /* Encode and add to ext file content (if needed) single label argument. */
            encodeDirectArg(instructions[*currWord + 1],
                            getArgData(firstArg).data.string,
                            normalLabels, extLabels, extFileContents, *currWord + 1);
            break;
        case DIRECT_REGISTER: /* Encode single register argument. */
            encodeDirectRegisterArg(instructions[*currWord + 1],
                                    getArgData(firstArg).data.reg, TRUE);
            break;
    }

    (*currWord) += TWO_INDEX;
}