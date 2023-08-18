/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the finals to determine the order of bits in the words of the
 * imaginary machine.
 */

#ifndef MMN_14_RANGES_H
#define MMN_14_RANGES_H

/* Ranges, as defined and explained in the encoding file's description. */
enum {OPCODE_LOW = 5, OPCODE_HIGH = 8, ARG_LOW = 2, ARG_HIGH = 11,
    DEST_MTD_LOW = 2, DEST_MTD_HIGH = 4, SRC_MTD_LOW = 9, SRC_MTD_HIGH = 11,
    DEST_REG_LOW = 2, DEST_REG_HIGH = 6, SRC_REG_LOW = 7, SRC_REG_HIGH = 11,
    DIR_DATA_LOW = 2, DIR_DATA_HIGH = 11,
    ARE_LOW = 0, ARE_HIGH = 1,
    DATA_LOW = 0, DATA_HIGH = 11,
    START_WORD_RANGE = 0, END_WORD_RANGE = 11};

#endif /* MMN_14_RANGES_H */
