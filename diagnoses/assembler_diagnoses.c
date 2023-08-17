/*
 * @author Ofir Paz
 * @version (15/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../new-data-types/boolean.h"
#include "../general-enums/indexes.h"
#include "../encoding/encoding-finals/encoding_finals.h"
#include "../assembler_ast/assembler_ast.h"
#include "../encoding/wordHandling.h"
/* -------------------------- */

/* ---Finals--- */
#define MAX_PARAM_COUNT 2
#define ONE_BIT 1
#define VALID_ARG 0
#define INVALID_ARG_MTD (-1)
#define INVALID_ARG_NUMBER (-2)
#define MAX_SIZE_FOR_DATA 12
#define MAX_BITS_FOR_INSTANT_VAL 10

enum {src, dest};
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
            opGroup = NO_OPCODE;
    }

    return opGroup;
}

/*
 * Validates the argument for the given opcode, type of argument (dest or src)
 * and addressing method.
 *
 * @param   opcode          The opcode to validate the argument against.
 * @param   isDest          Flag indicating if the argument is the destination argument.
 * @param   addMtd          The addressing method of the argument.
 *
 * @return  The validation result: VALID_ARG (0) if the argument is valid,
 *          INVALID_ARG_MTD (-1) if the addressing method is invalid,
 *          INVALID_ARG_NUMBER (-2) if the isDest flag is not matching the opcode.
 */
int validArg(opcodes_t opcode, boolean isDest, addressing_method_t addMtd)
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

    int validArg; /* Value to return. */
    int argIndex = (isDest)? ONE_INDEX : ZERO_INDEX; /* Index of argument in table. */

    if (addressingMethodsTable[opcode][argIndex] == ZERO_ADD_MTD)
        validArg = INVALID_ARG_NUMBER;

    /* Check if the argument addressing method matches the one in the table. */
    else if (addressingMethodsTable[opcode][argIndex] & (ONE_BIT << addMtd))
        validArg = VALID_ARG;
    else
        validArg = INVALID_ARG_MTD;

    return validArg;
}

/*
 * Checks if the operation with the given opcode requires the argument
 * with the give number.
 *
 * @param   opcode          The opcode of the operation to check.
 * @param   argumentNum     The argument number to check if needed.
 *
 * @return  TRUE if the argument is needed, otherwise FALSE.
 */
boolean isNeedArgument(opcodes_t opcode, int argumentNum)
{
    op_group_t opGroup = getOpGroup(opcode);

    return (argumentNum <= opGroup)? TRUE : FALSE;
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

    /* The command is an operation. If need another argument - */
    else if (isNeedArgument(opcode, argumentNum + 1) == TRUE)
        areaStatus = MUST_BE_ANOTHER_ARG;

    else /* The command is an operation and there can't be another argument. */
        areaStatus = LAST_ARG;

    return areaStatus;
}

/*
 * Checks if all arguments in the given argument node have a specific data type.
 *
 * @param   *argNode        The first of the arguments to check.
 * @param   dataType        The specific data type to check against.
 *
 * @return  TRUE if all arguments have the specified data type, otherwise FALSE.
 */
boolean isAllArgsSpecificDataType(arg_node_t *argNode, data_type_t dataType)
{
    boolean isAllArgsSpecificDataType = TRUE; /* Value to return. */

    /* Go through all the arguments and check for a mismatch in the data type. */
    while (argNode != NULL && isAllArgsSpecificDataType == TRUE)
    {
        if (getArgData(argNode).dataType != dataType)
            isAllArgsSpecificDataType = FALSE;
        argNode = getNextNode(argNode);
    }

    return isAllArgsSpecificDataType;
}

/*
 * Checks if the given argument node has number overflow.
 * For data number, 12 bits can be used and for an instant value number, 10 bits.
 *
 * @param   *argNode        The argument node to check.
 * @param   isData          Indicates whether the argument is for data or not.
 *
 * @return  TRUE if the given argument node has number overflow, otherwise FALSE.
 */
boolean isOverflowNumber(arg_node_t *argNode, boolean isData)
{
    boolean isOverflowNumber = FALSE; /* Value to return. */

    /* Check if there is a possibility for an overflow. */
    if (argNode != NULL && getArgData(argNode).dataType == INT)
    {
        /* Check if there is an overflow. */
        if (isData == TRUE)
            isOverflowNumber = isOverflow(MAX_SIZE_FOR_DATA, getArgData(argNode).data.num);
        else
            isOverflowNumber = isOverflow(MAX_BITS_FOR_INSTANT_VAL, getArgData(argNode).data.num);
    }

    return isOverflowNumber;
}

/*
 * Checks if the given and in the next argument nodes there is a number overflow.
 * For data number, 12 bits can be used and for an instant value number, 10 bits.
 *
 * @param   *argNode        The argument node to check from.
 * @param   isData          Indicates whether the arguments are for data or not.
 *
 * @return  TRUE if the given and in the next argument nodes there is a number overflow,
 *          otherwise FALSE.
 */
boolean isAnyOverflowNumber(arg_node_t *argNode, boolean isData)
{
    boolean isAnyOverflowNumber = FALSE; /* Value to return. */

    /* Go through all arguments while we haven't found an overflow. */
    while (argNode != NULL && isAnyOverflowNumber == FALSE)
    {
        /* Check for overflow in the current argument. */
        isAnyOverflowNumber = isOverflowNumber(argNode, isData);

        argNode = getNextNode(argNode); /* Check next argument. */
    }

    return isAnyOverflowNumber;
}