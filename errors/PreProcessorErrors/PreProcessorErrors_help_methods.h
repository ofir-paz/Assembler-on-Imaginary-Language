/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * Header file for the PreProcessorErrors_help_methods.c file.
 */

#ifndef MMN_14_PREPROCESSORERRORS_HELP_METHODS_H
#define MMN_14_PREPROCESSORERRORS_HELP_METHODS_H

#include "../../new-data-types/boolean.h"

/* ---------------Prototypes--------------- */

/*
 * Checks if the first word in the given line is a macro saved word in the language.
 * The saved words are: "mcro" and "endmcro".
 *
 * @param   *line The given line string to check the first word in it.
 * @return  TRUE if the first word is a macro saved word, otherwise FALSE.
 */
boolean isFirstWordMcroDef(const char *line);

/* ---------------------------------------- */

#endif /* MMN_14_PREPROCESSORERRORS_HELP_METHODS_H */
