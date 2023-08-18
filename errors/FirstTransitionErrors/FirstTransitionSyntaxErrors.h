/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the FirstTransitionErrors.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONSYNTAXERRORS_H
#define MMN_14_FIRSTTRANSITIONSYNTAXERRORS_H

/* ---------------Prototypes--------------- */

/*
 * Checks for syntax errors in label definition.
 * Assuming there is a colon in the line, and his position is not beyond the start
 * of the second word.
 *
 * @param   *line   The line to check for errors in.
 *
 * @return  The label definition syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInLabel(const char *line);

/*
 * Checks for syntax errors in the command of the given line.
 *
 * @param   line        The input line to check for syntax errors in its command.
 * @param   isLabelDef  Flag indicating if the line has a label definition.
 *
 * @return  The command syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInCommand(const char *line, boolean isLabelDef);

/*
 * Checks for a syntax error in the argument and the space between arguments in the given line.
 *
 * @param   *line           The line of assembly code to check for syntax errors.
 * @param   argumentNum     The number of the argument to check for (starting from 1).
 * @param   isLabelDef      Indicates whether the line has a label definition or not.
 * @param   opcode          The opcode of the operation that is in the line
 *                          (NO_OPCODE for guidance).
 * @param   isStrGuidance   Flag indicating if the line has a .string guidance.
 *
 * @return  The argument\space syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInArgAndBetween(const char *line, int argumentNum, boolean isLabelDef,
                                            opcodes_t opcode, boolean isStrGuidance);

/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONSYNTAXERRORS_H */
