/*
 * @author Ofir Paz
 * @version (14/08/2023)
 *
 * Header file for the FirstTransitionSpecificErrorCheck.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H
#define MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H

/* ---------------Prototypes--------------- */

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

/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONSPECIFICERRORCHECK_H */
