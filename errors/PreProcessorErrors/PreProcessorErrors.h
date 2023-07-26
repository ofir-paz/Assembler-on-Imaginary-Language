/*
 * @author Ofir Paz
 * @version (07/07/2023)
 *
 * Header file for the PreProcessorErrors.c file.
 */

#ifndef MMN_14_PREPROCESSORERRORS_H
#define MMN_14_PREPROCESSORERRORS_H

/* ---------------Prototypes--------------- */

Error handlePreProcessErrors(const char *line, int lineNumber, const char *macro_name,
                             boolean isMacroLine);

/* ---------------------------------------- */

#endif /* MMN_14_PREPROCESSORERRORS_H */
