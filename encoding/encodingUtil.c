/*
 * @author Ofir Paz
 * @version (09/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../assembler_ast/assembler_ast.h"
#include "encodingDataStructures/MemoryImage.h"
#include "encoding-finals/ranges.h"
#include "wordHandling.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define ZERO_BYTE 0
/* ------------ */

/* ---------------Prototypes--------------- */
void encodeToWordARE(word_t word, encoding_type_t encodingType);
/* ---------------------------------------- */

/*
 * Encodes a partial directive instruction to the given word array.
 *
 * @param   instructions  The word array to encode the instruction into.
 * @param   currWord      The current word index in the array.
 * @param   opcode        The opcode to encode.
 */
void encodePartDir(word_t *instructions, int currWord, opcodes_t opcode)
{
    /* Encode opcode. */
    setBitsInRangeToVal(instructions[currWord], OPCODE_LOW, OPCODE_HIGH,opcode);
    /* Encode known A, R, E field (instruction is always absolute). */
    encodeToWordARE(instructions[currWord], ABSOLUTE);
}

/*
 * Encodes an immediate argument to the given word.
 *
 * @param   word         The word to encode the immediate argument to.
 * @param   instantVal   The immediate value to be encoded.
 */
void encodeInstantArg(word_t word, int instantVal)
{
    /* instant value is independent of where the program will be loaded to the memory. */
    encodeToWordARE(word, ABSOLUTE);
    setBitsInRangeToVal(word, DIR_DATA_LOW,DIR_DATA_HIGH, instantVal);
}

/*
 * Encodes a direct argument to the given word using the provided parameters.
 *
 * @param   word              The word to encode the direct argument to.
 * @param   directLabel       The label for the direct argument.
 * @param   normalLabels      A table containing normal (internal) labels.
 * @param   extLabels         A table containing external labels.
 * @param   extFileContents   Pointer to string of external file contents.
 * @param   address           The current address for relative addressing calculations.
 */
void encodeDirectArg(word_t word, int address, const char *directLabel, NameTable *normalLabels,
                     NameTable *extLabels, char **extFileContents)
{
    /* Get the label value from the extern table (if it's there). */
    name_data_t *labelVal = getDataByName(normalLabels, directLabel);

    if (labelVal != NULL) /* Label in argument is defined in this file. */
    {
        encodeToWordARE(word, RELOCATABLE); /* Relocatable encoding. */
        setBitsInRangeToVal(word, DIR_DATA_LOW, DIR_DATA_HIGH, labelVal -> num);
    }
    else /* Label in argument is an extern label. */
    {
        encodeToWordARE(word, EXTERNAL); /* External encoding */
        /* The address will be found in the linking stage. */
        setBitsInRangeToVal(word, DIR_DATA_LOW, DIR_DATA_HIGH, ZERO_BYTE);
        addToStringInFormat(extFileContents, directLabel, address);
    }
}

/*
 * Encodes to the given word registers arguments.
 *
 * @param   word        The word to encode the register argument to.
 * @param   destReg     The destination register to be encoded as a direct register argument.
 * @param   srcReg      The source register to be encoded as a direct register argument.
 */
void encodeDirectRegisterArg(word_t word, register_t destReg, register_t srcReg)
{
    /* Register is independent of where the program will be loaded to the memory. */
    encodeToWordARE(word, ABSOLUTE);

    /* Encode registers. */
    setBitsInRangeToVal(word, DEST_REG_LOW, DEST_REG_HIGH, (int) destReg);
    setBitsInRangeToVal(word, SRC_REG_LOW, SRC_REG_HIGH, (int) srcReg);
}

/*
 * Encodes an argument of a direction to the given word.
 *
 * @param   word              The word to encode the argument to.
 * @param   address           The address of the word in the memory.
 * @param   argument          The argument to encode.
 * @param   isDest            Flag indicating if the argument is for the destination operand.
 * @param   normalLabels      Table of normal labels.
 * @param   extLabels         Table of external labels.
 * @param   extFileContents   Pointer to string of external file contents.
 */
void encodeDirArgument(word_t word, int address, arg_node_t *argument, boolean isDest,
                       NameTable *normalLabels, NameTable *extLabels, char **extFileContents)
{
    addressing_method_t argMtd = getArgAddressingMethod(argument); /* Get. mtd */

    switch (argMtd) /* We assume argMtd must fall in one of these switch cases. */
    {
        case INSTANT: /* Encode single instant value argument. */
            encodeInstantArg(word, getArgData(argument).data.num);
            break;
        case DIRECT: /* Encode and add to ext file content (if needed) single label argument. */
            encodeDirectArg(word, address, getArgData(argument).data.string,
                            normalLabels, extLabels, extFileContents);
            break;
        case DIRECT_REGISTER: /* Encode single register argument. */
            if (isDest == TRUE)
                encodeDirectRegisterArg(word,getArgData(argument).data.reg,
                                        ZERO_BYTE);
            else
                encodeDirectRegisterArg(word, ZERO_BYTE,
                                        getArgData(argument).data.reg);
            break;
        default: break;
    }
}

/*
 * Encodes a data value into the given data word array.
 *
 * @param   data        The data word array to encode the data value into.
 * @param   currData    The current data index in the array.
 * @param   dataVal     The data value to encode.
 */
void encodeDataVal(word_t *data, int currData, int dataVal)
{
    setBitsInRangeToVal(data[currData], DATA_LOW, DATA_HIGH, dataVal);
}

/*
 * Encodes the addressing methods for the destination and source operands to the given word.
 *
 * @param   word       The word to encode the addressing methods to.
 * @param   destMtd    The addressing method for the destination operand.
 * @param   srcMtd     The addressing method for the source operand.
 */
void encodeAddressingMethods(word_t word, addressing_method_t destMtd, addressing_method_t srcMtd)
{
    setBitsInRangeToVal(word, DEST_MTD_LOW, DEST_MTD_HIGH, destMtd); /* Dest. */
    setBitsInRangeToVal(word, SRC_MTD_LOW, SRC_MTD_HIGH, srcMtd); /* Source. */
}

/*
 * Encodes the A, R, E field to a given word.
 *
 * @param   word            The word to encode the A, R, E field to.
 * @param   encodingType    The specific ARE to be used for encoding.
 */
void encodeToWordARE(word_t word, encoding_type_t encodingType)
{
    setBitsInRangeToVal(word, ARE_LOW, ARE_HIGH, encodingType);
}