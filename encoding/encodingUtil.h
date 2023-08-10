/*
 * @author Ofir Paz
 * @version (09/08/2023)
 *
 * Header file for the encodingUtil.c file.
 */

#ifndef MMN_14_ENCODINGUTIL_H
#define MMN_14_ENCODINGUTIL_H

/* ---------------Prototypes--------------- */

/*
 * Encodes a partial directive instruction to the given word array.
 *
 * @param   instructions  The word array to encode the instruction into.
 * @param   currWord      The current word index in the array.
 * @param   opcode        The opcode to encode.
 */
void encodePartDir(word_t *instructions, int currWord, opcodes_t opcode);

/*
 * Encodes to the given word registers arguments.
 *
 * @param   word        The word to encode the register argument to.
 * @param   destReg     The destination register to be encoded as a direct register argument.
 * @param   srcReg      The source register to be encoded as a direct register argument.
 */
void encodeDirectRegisterArg(word_t word, reg_t destReg, reg_t srcReg);

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
                       NameTable *normalLabels, NameTable *extLabels, char **extFileContents);

/*
 * Encodes a data value into the given data word array.
 *
 * @param   data        The data word array to encode the data value into.
 * @param   currData    The current data index in the array.
 * @param   dataVal     The data value to encode.
 */
void encodeDataVal(word_t *data, int currData, int dataVal);

/*
 * Encodes the addressing methods for the destination and source operands to the given word.
 *
 * @param   word       The word to encode the addressing methods to.
 * @param   destMtd    The addressing method for the destination operand.
 * @param   srcMtd     The addressing method for the source operand.
 */
void encodeAddressingMethods(word_t word, addressing_method_t destMtd, addressing_method_t srcMtd);

/*
 * Encodes the A, R, E field to a given word.
 *
 * @param   word            The word to encode the A, R, E field to.
 * @param   encodingType    The specific ARE to be used for encoding.
 */
void encodeToWordARE(word_t word, encoding_type_t encodingType);

/* ---------------------------------------- */

#endif /* MMN_14_ENCODINGUTIL_H */
