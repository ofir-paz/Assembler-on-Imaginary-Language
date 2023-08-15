/*
 * @author Ofir Paz
 * @version (15/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "../encoding/encoding-finals/encoding_finals.h"
/* -------------------------- */

/* ---Finals--- */
#define MAX_PARAM_COUNT 2
#define ONE_BIT 1
/* ------------ */

/* ---Macros--- */
#define inst_B (ONE_BIT << INSTANT)
#define dir_B (ONE_BIT << DIRECT)
#define reg_B (ONE_BIT << DIRECT_REGISTER)
/* ------------ */

typedef enum {ZERO_PARAMS, ONE_PARAMS, TWO_PARAMS} op_group_t;

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

op_group_t getOpGroup(opcodes_t opcode)
{
    op_group_t opGroup;

    switch (opcode)
    {
        case mov: case cmp: case add: case sub:
            opGroup = TWO_PARAMS; break;

        case not: case clr:
            opGroup = ONE_PARAMS; break;

        case lea:
            opGroup = TWO_PARAMS; break;

        case inc: case dec: case jmp: case bne: case red: case prn: case jsr:
            opGroup = ONE_PARAMS; break;

        case rts: case stop:
            opGroup = ZERO_PARAMS; break;

        default:
            opGroup = ZERO_PARAMS;
    }

    return opGroup;
}

boolean isValidAddMtd(opcodes_t opcode, int argumentNum, addressing_method_t addMtd)
{
    /* Table representing valid addressing method for every operation. */
    char addressingMethodsTable[OPCODE_AMOUNT][MAX_PARAM_COUNT] =
            {
                    {inst_B | dir_B | reg_B,             dir_B | reg_B},    /* mov */
                    {inst_B | dir_B | reg_B,    inst_B | dir_B | reg_B},    /* cmp */
                    {inst_B | dir_B | reg_B,             dir_B | reg_B},    /* add */
                    {inst_B | dir_B | reg_B,             dir_B | reg_B},    /* sub */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* not */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* clr */
                    {         dir_B,                     dir_B | reg_B},    /* lea */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* inc */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* dec */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* jmp */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* bne */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* red */
                    {ZERO_ADD_MTD,              inst_B | dir_B | reg_B},    /* prn */
                    {ZERO_ADD_MTD,                       dir_B | reg_B},    /* jsr */
                    {ZERO_ADD_MTD, ZERO_ADD_MTD},                           /* rts */
                    {ZERO_ADD_MTD, ZERO_ADD_MTD},                           /* stop */
            };

    boolean isValidAddMtd = FALSE;
    if (--argumentNum > MAX_PARAM_COUNT)
        if (addressingMethodsTable[opcode][argumentNum] & (ONE_BIT << addMtd))
                isValidAddMtd = TRUE;

    return isValidAddMtd;
}