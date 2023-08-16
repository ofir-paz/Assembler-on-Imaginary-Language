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
#define VALID_ARG 0
#define INVALID_ARG_MTD (-1)
#define INVALID_ARG_NUMBER (-2)
/* ------------ */

/* ---Macros--- */
#define inst_B (ONE_BIT << INSTANT)
#define dir_B (ONE_BIT << DIRECT)
#define reg_B (ONE_BIT << DIRECT_REGISTER)
/* ------------ */

/* Groups of operations by the amount of arguments they accept. */
typedef enum {ZERO_ARGS, ONE_ARGS, TWO_ARGS} op_group_t;

/* Indicates the state of the area between arguments. */
typedef enum {LAST_ARG, CAN_BE_ANOTHER_ARG, MUST_BE_ANOTHER_ARG} area_status_t;

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Gets the operation group based on the given opcode.
 * The operation group informs about how many arguments the operation accepts.
 *
 * @param   opcode  The opcode to determine the operation group for.
 *
 * @return  The operation group of the specified opcode.
 */
op_group_t getOpGroup(opcodes_t opcode)
{
    op_group_t opGroup;

    /* Finding which operation group does the given operation belongs to.
     * Used a switch here instead of 'if' statements (which will look better)
     * because it is faster. */
    switch (opcode)
    {
        case mov: case cmp: case add: case sub:
            opGroup = TWO_ARGS; break;

        case not: case clr:
            opGroup = ONE_ARGS; break;

        case lea:
            opGroup = TWO_ARGS; break;

        case inc: case dec: case jmp: case bne: case red: case prn: case jsr:
            opGroup = ONE_ARGS; break;

        case rts: case stop:
            opGroup = ZERO_ARGS; break;

        default:
            opGroup = ZERO_ARGS;
    }

    return opGroup;
}

/*
 * Validates the argument for the given opcode, argument number, and addressing method.
 *
 * @param   opcode          The opcode to validate the argument against.
 * @param   argumentNum     The argument number to validate.
 * @param   addMtd          The addressing method of the argument.
 *
 * @return  The validation result: VALID_ARG (0) if the argument is valid,
 *          INVALID_ARG_MTD (-1) if the addressing method is invalid,
 *          INVALID_ARG_NUMBER (-2) if the argument number is invalid.
 */
int validArg(opcodes_t opcode, int argumentNum, addressing_method_t addMtd)
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

    int validArg = INVALID_ARG_NUMBER; /* Value to return, assume the number is invalid. */

    /* Decrease argumentNum because index of argument starts in 1. */
    if (argumentNum-- < MAX_PARAM_COUNT) /* Check if the number is valid. */
    {
        /* Check if the argument addressing method matches the one in the table. */
        if (addressingMethodsTable[opcode][argumentNum] & (ONE_BIT << addMtd))
            validArg = VALID_ARG;
        else
            validArg = INVALID_ARG_MTD;
    }

    return validArg;
}

/*
 * Gets the area status after an argument for the given opcode, argument number, and guidance type.
 * Area status informs about the possibility of another argument.
 *
 * @param   opcode          The opcode to check (could be NO_OPCODE).
 * @param   isStrGuidance   Indicates if the command is a string guidance (.string).
 * @param   argumentNum     The argument number to check the empty space status after it.
 *
 * @return  The empty status indicating if an argument is expected or not.
 */
area_status_t getAreaStatus(opcodes_t opcode, boolean isStrGuidance, int argumentNum)
{
    area_status_t areaStatus;

    /* If the command is a guidance (not .string), unlimited number of arguments. */
    if (opcode == NO_OPCODE)
        areaStatus = (isStrGuidance == TRUE)? LAST_ARG : CAN_BE_ANOTHER_ARG;

        /* The command is an operation. If there can't be another argument - */
    else if (validArg(opcode, argumentNum + 1, ZERO_ADD_MTD) == INVALID_ARG_NUMBER)
        areaStatus = LAST_ARG;

    else /* The command is an operation and there must be another argument. */
        areaStatus = MUST_BE_ANOTHER_ARG;

    return areaStatus;
}