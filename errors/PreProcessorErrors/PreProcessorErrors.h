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

Error handlePreProcessErrors(const char *file_name, const char *line, int lineNumber,
                             const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef);

/* ---------------------------------------- */

#endif /* MMN_14_PREPROCESSORERRORS_H */