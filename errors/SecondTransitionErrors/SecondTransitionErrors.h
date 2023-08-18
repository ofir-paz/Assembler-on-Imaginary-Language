/*
 * @author Ofir Paz
 * @version (12/08/2023)
 *
 * Header file for the SecondTransitionErrors.c file.
 */

#ifndef MMN_14_SECONDTRANSITIONERRORS_H
#define MMN_14_SECONDTRANSITIONERRORS_H

#include "../../new-data-types/boolean.h"
#include "../error_types/error_types.h"

/* ---------------Prototypes--------------- */

typedef struct NameTable NameTable;
typedef struct ast_t ast_t;

/*
 * Handles a line error during the second transition phase, updating the error status.
 * Will do nothing if there was no error.
 *
 * @param   *file_name      The name of the file where the error occurred.
 * @param   currLine        The current line number where the error occurred.
 * @param   lineError       The specific error that occurred (can be NO_ERROR).
 * @param   *wasError       Pointer to a boolean indicating whether an error was encountered.
 */
void handleLineErrorInSecondTrans(const char *file_name, int currLine, Error lineError,
                                  boolean *wasError);


/*
 * Checks for a logical error related to an entry label.
 * The only logical error that needs to be checked in the second transition is
 * whether an entry label is defined in the file.
 *
 * @param   *entLabel       The entry label to check for errors.
 * @param   *normalLabels   Pointer to the NameTable containing normal labels.
 *
 * @return  The specific error found, or NO_ERROR if there was no error.
 */
LogicalError checkEntryLabelError(const char *entLabel, NameTable *normalLabels);

/*
 * Checks for a logical error related to an undefined label argument.
 *
 * @param   *lineAst        The Abstract Syntax Tree (AST) for the line to check.
 * @param   *normalLabels   Pointer to the NameTable containing normal labels.
 * @param   *extLabels      Pointer to the NameTable containing external labels.
 *
 * @return  The specific error found, or NO_ERROR if there was no error.
 */
LogicalError checkUndefinedLabelArgumentError(ast_t *lineAst, NameTable *normalLabels,
                                              NameTable *extLabels);

/* ---------------------------------------- */

#endif /* MMN_14_SECONDTRANSITIONERRORS_H */
