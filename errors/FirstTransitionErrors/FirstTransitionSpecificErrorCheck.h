/*
 * @author Ofir Paz
 * @version (14/08/2023)
 *
 * Header file for the FirstTransitionSpecificErrorCheck.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H
#define MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H

/* ---------------Prototypes--------------- */


/* ---------------LABEL SYNTAX ERRORS--------------- */

/*
 * Checks if a label is missing in the given line.
 * Assuming the line starts with the label definition and that it has a colon in it.
 *
 * @param   *labelLine  The line of assembly code to check for a missing label.
 *
 * @return  TRUE if a label is missing in the given line, otherwise FALSE.
 */
boolean isMissingLabel(const char *labelLine);

/*
 * Checks if there is no empty space between a label and the colon in the given label line.
 *
 * @param   *labelLine  The line of assembly code to check for empty space between label and colon.
 *
 * @return  TRUE if there is empty space between the label and colon, otherwise FALSE.
 */
boolean isEmptyBetweenLabelAndColon(const char *labelLine);

/*
 * Checks if the label in the given label line starts with a number.
 *
 * @param   *labelLine  The line of assembly code to check for a label that starts with a number.
 *
 * @return  TRUE if the label starts with a number, otherwise FALSE.
 */
boolean isLabelStartWithNumber(const char *labelLine);

/*
 * Checks if the label in the given label line starts with an illegal character.
 *
 * @param   *labelLine  The line of assembly code to check for a label that starts with
 *                      an illegal character.
 *
 * @return  TRUE if the label starts with an illegal character, otherwise FALSE.
 */
boolean isLabelStartWithIllegalChar(const char *labelLine);

/*
 * Checks if the label in the given label line contains any illegal characters.
 *
 * @param   *labelLine  The line of assembly code to check for a label that contains
 *                      illegal characters.
 *
 * @return  TRUE if the label contains illegal characters, otherwise FALSE.
 */
boolean isLabelContainsIllegalChar(const char *labelLine);

/*
 * Checks if the label in the given label line is too long (exceeds the maximum allowed length).
 *
 * @param   *labelLine  The line of assembly code to check for a label that is too long.
 *
 * @return  TRUE if the label is too long, otherwise FALSE.
 */
boolean isLabelTooLong(const char *labelLine);

/*
 * Checks if the label in the given label line matches a saved word
 * (e.g., an assembler guidance, opcode or register).
 *
 * @param   *labelLine  The line of assembly code to check for a label that matches a saved word.
 *
 * @return  TRUE if the label matches a saved word, otherwise FALSE.
 */
boolean isLabelSavedWord(const char *labelLine);

/*
 * Checks if there are multiple consecutive colons in the given line after the label.
 *
 * @param   *labelLine      The line of assembly code to check for multiple consecutive colons.
 *
 * @return  TRUE if there are multiple consecutive colons after the label in the given line,
 *          otherwise FALSE.
 */
boolean isMultipleConsColons(const char *labelLine);

/*
 * Checks if there is a comma after the label in the given line.
 *
 * @param   *labelLine      The line of assembly code to check for a comma after the label.
 *
 * @return  TRUE if there is a comma after the label in the given line, otherwise FALSE.
 */
boolean isCommaAfterLabel(const char *labelLine);

/* ---------------END OF LABEL SYNTAX ERRORS--------------- */


/* ---------------GENERAL COMMAND SYNTAX ERRORS--------------- */

/*
 * Checks if the given line is missing an operation or guidance.
 *
 * @param   *commandLine    The line of assembly code to check for missing operation or guidance.
 *
 * @return  TRUE if the given line is missing an operation or guidance, otherwise FALSE.
 */
boolean isMissingOpOrGui(const char *commandLine);

/*
 * Checks if there is a comma after the command in the given line.
 *
 * @param   *commandLine    The line of assembly code to check for a comma after the command.
 *
 * @return  TRUE if there is a comma after the command in the given line, otherwise FALSE.
 */
boolean isCommaAfterCmd(const char *commandLine);

/* ---------------END OF GENERAL COMMAND SYNTAX ERRORS--------------- */


/* ---------------GUIDANCE SYNTAX ERRORS--------------- */

/*
 * Checks if a guidance is missing in the given line.
 * Assuming the line starts with a dot.
 *
 * @param   *labelLine  The line of assembly code to check for a missing guidance.
 *
 * @return  TRUE if a guidance is missing in the given line, otherwise FALSE.
 */
boolean isMissingGuidance(const char *guidanceLine);

/*
 * Checks if the given line contains multiple consecutive dots in a guidance
 * (if it's valid or not).
 *
 * @param   *guidanceLine   The line of assembly code to check for multiple dots.
 *
 * @return  TRUE if the given line contains guidance with multiple dots, otherwise FALSE.
 */
boolean isMultConsDotsInGuidance(const char *guidanceLine);

/*
 * Checks if the given line has a different case guidance.
 *
 * @param   *guidanceLine   The line of assembly code to check for different case guidance.
 *
 * @return  TRUE if the given line has a different case guidance, otherwise FALSE.
 */
boolean isDifferentCaseGuidance(const char *guidanceLine);

/* ---------------END OF GUIDANCE SYNTAX ERRORS--------------- */


/* ---------------OPERATION SYNTAX ERRORS--------------- */

/*
 * Checks if the given line has a guidance but is missing a dot at the start.
 *
 * @param   *operationLine   The line of assembly code to check for a missing dot in the guidance.
 *
 * @return  TRUE if the given line is a guidance but is missing a dot, otherwise FALSE.
 */
boolean isGuidanceButMissingDot(const char *operationLine);

/*
 * Checks if the given line has a different case operation.
 *
 * @param   *operationLine   The line of assembly code to check for different case operation.
 *
 * @return  TRUE if the given line has a different case operation, otherwise FALSE.
 */
boolean isDifferentCaseOperation(const char *operationLine);

/* ---------------END OF OPERATION SYNTAX ERRORS--------------- */


/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H */
