/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains the new data type 'opcodes_t'.
 */

#ifndef MMN_14_OPCODES_H
#define MMN_14_OPCODES_H

/* Represents all the opcodes. */
typedef enum {NO_OPCODE = -1,
              mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop,
              OPCODE_AMOUNT} opcodes_t;

#endif /* MMN_14_OPCODES_H */