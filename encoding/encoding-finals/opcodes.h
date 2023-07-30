/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'boolean'.
 * */

#ifndef MMN_14_OPCODES_H
#define MMN_14_OPCODES_H

typedef enum {mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop,
              NO_OPCODE = -1} opcodes_t;

#endif /* MMN_14_OPCODES_H */