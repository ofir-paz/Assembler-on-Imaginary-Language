/*
 * @author Ofir Paz
 * @version (18/07/2023)
 *
 * Header file for the PreProcessorErrors.c file.
 */

#ifndef MMN_14_PREPROCESSORERRORS_H
#define MMN_14_PREPROCESSORERRORS_H

#include "../../new-data-types/boolean.h"

/* ---------------Prototypes--------------- */

/* ---Typedef prototype for encapsulation--- */
typedef int Error;
/* ----------------------------------------- */

/*
 * Checks for errors related to pre-processing during assembly.
 *
 * @param   *line           The input line of assembly code.
 * @param   *macro_name     The name of the macro being defined or used (if applicable).
 * @param   wasInMacroDef   Indicates if the previous line was within a macro definition.
 * @param   isInMacroDef    Indicates if the current line is within a macro definition.
 *
 * @return  An error code indicating the type of pre-processing error,
 *          or NO_ERROR if no error is found.
 */
Error checkPreProcessErrors(const char *line, const char *macro_name,
                            boolean wasInMacroDef, boolean isInMacroDef);

/*
 * Checks if a given line of text exceeds a specified maximum length.
 * In this assembly language, the maximum line length is 80, not including the new line char.
 *
 * @param   *line   The input line of text to check.
 *
 * @return  TRUE if the line exceeds the maximum length, otherwise FALSE.
 */
boolean isLineTooLong(const char *line);

/* ---------------------------------------- */

#endif /* MMN_14_PREPROCESSORERRORS_H */
