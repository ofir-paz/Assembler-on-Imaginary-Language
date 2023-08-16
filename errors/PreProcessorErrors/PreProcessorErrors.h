/*
 * @author Ofir Paz
 * @version (07/07/2023)
 *
 * Header file for the PreProcessorErrors.c file.
 */

#ifndef MMN_14_PREPROCESSORERRORS_H
#define MMN_14_PREPROCESSORERRORS_H

#include "../error_types/error_types.h"

/* ---------------Prototypes--------------- */

Error checkPreProcessErrors(const char *file_name, const char *line, int lineNumber,
                            const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef);

/* Checks if an input line is too long ( > 80).
 * param const char *line is the input line.
 * Returns TRUE if the line is too long, otherwise FALSE. */
boolean isLineTooLong(const char *line);

/* ---------------------------------------- */

#endif /* MMN_14_PREPROCESSORERRORS_H */
