/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the assembler_diagnoses.c file.
 */

#ifndef MMN_14_ASSEMBLER_DIAGNOSES_H
#define MMN_14_ASSEMBLER_DIAGNOSES_H

/* Return values. */
#define VALID_ARG 0
#define INVALID_ARG_MTD (-1)
#define INVALID_ARG_NUMBER (-2)

/* Groups of operations by the amount of arguments they accept. */
typedef enum {ZERO_ARGS, ONE_ARGS, TWO_ARGS} op_group_t;

/* Indicates the state of the area between arguments. */
typedef enum {LAST_ARG, CAN_BE_ANOTHER_ARG, MUST_BE_ANOTHER_ARG} area_status_t;

/* validArg function return codes. */
#define VALID_ARG 0
#define INVALID_ARG_MTD (-1)
#define INVALID_ARG_NUMBER (-2)

/* ---------------Prototypes--------------- */

/*
 * Gets the operation group based on the given opcode.
 * The operation group informs about how many arguments the operation accepts.
 *
 * @param   opcode  The opcode to determine the operation group for.
 *
 * @return  The operation group of the specified opcode.
 */
op_group_t getOpGroup(opcodes_t opcode);

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
int validArg(opcodes_t opcode, boolean isDest, addressing_method_t addMtd);

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
area_status_t getAreaStatus(opcodes_t opcode, boolean isStrGuidance, int argumentNum);

/*
 * Checks if all arguments in the given argument node have a specific data type.
 *
 * @param   *argNode        The first of the arguments to check.
 * @param   dataType        The specific data type to check against.
 *
 * @return  TRUE if all arguments have the specified data type, otherwise FALSE.
 */
boolean isAllArgsSpecificDataType(arg_node_t *argNode, data_type_t dataType);

/*
 * Checks if the given argument node has number overflow.
 * For data number, 12 bits can be used and for an instant value number, 10 bits.
 *
 * @param   *argNode        The argument node to check.
 * @param   isData          Indicates whether the argument is for data or not.
 *
 * @return  TRUE if the given argument node has number overflow, otherwise FALSE.
 */
boolean isOverflowNumber(arg_node_t *argNode, boolean isData);

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
boolean isAnyOverflowNumber(arg_node_t *argNode, boolean isData);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_DIAGNOSES_H */
