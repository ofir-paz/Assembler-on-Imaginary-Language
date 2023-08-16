/*
 * @author Ofir Paz
 * @version (15/08/2023)
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
int validArg(opcodes_t opcode, int argumentNum, addressing_method_t addMtd);

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

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_DIAGNOSES_H */
