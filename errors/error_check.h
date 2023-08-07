/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the error_check.c file
 */

#ifndef MMN_22_ERROR_CHECK_H
#define MMN_22_ERROR_CHECK_H

#include "error_types/error_types.h"
#include "../new-data-types/boolean.h"
#include "../new-data-types/word_number.h"

/* ------------------Prototypes------------------- */

/* Checks if the given pointer *ptr has allocated space in the memory.
 * Returns TRUE if it has, otherwise FALSE. */
boolean isAllocated(void *ptr);

/* Checks if the param const char *command is a valid function.
 * If it is, returns NO_ERROR, otherwise returns the specific error caught. */
Error checkCommandError(const char *command);

/* Checks if the area in param const char *line between the end index of
 * the parameter in line numbered paramNum with type pType and the index
 * of the next param is valid (comma-wise)
 * Returns NO_ERROR if it's valid, otherwise the specific error that occurs. */
Error checkCommaError(const char *line, word_number paramNum);//, paramtype pType);

/* Checks if float param number paramNum in const char *line is valid.
 * Returns NO_ERROR if it is, otherwise the specific error caught. */
Error checkParamFloatError(const char *line, word_number paramNum);

/* Checks for errors in the param numbered paramNum of const char *line.
 * Returns NO_ERROR if there is no error, otherwise the specific error caught. */
Error checkParamCharError(const char *line, word_number paramNum);

/*
 * Checks for extraneous text error in the given line starting from the specified index.
 *
 * @param   line              The input line to check for errors.
 * @param   indexOfLastToken  The index of the last token in the line before the error check.
 * @return                    Specific extraneous text error.
 */
Error checkExtraneousTextError(const char *line, int indexOfLastToken);

/* Checks if an input line is too long ( > 80).
 * param const char *line is the input line.
 * Returns TRUE if the line is too long, otherwise FALSE. */
boolean isLineTooLong(const char *line);
/* ---------------End of prototypes--------------- */

#endif /* MMN_22_ERROR_CHECK_H */
