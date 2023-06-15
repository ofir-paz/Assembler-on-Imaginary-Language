/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the error_check.c file
 */

#ifndef MMN_22_ERROR_CHECK_H
#define MMN_22_ERROR_CHECK_H

#include "../new-data-types/boolean.h"
#include "../new-data-types/Error.h"
#include "../general-enums/cmd_params.h"
#include "../new-data-types/paramType.h"
#include "StopState.h"

/* ------------------Prototypes------------------- */

/* Checks if the given pointer *ptr has allocated space in the memory.
 * Returns TRUE if it has, otherwise FALSE. */
boolean isAllocated(void *ptr);

/* Returns TRUE if param const char *line is an empty line {enter,null}, otherwise FALSE. */
boolean isEmptyLine(const char *line);

/* Checks if the param int i is an index of param const char *str.
 * Returns TRUE if i is an index of the given string, otherwise FALSE. */
boolean isIndexInStr(const char *str, int i);

/* Checks if the param const char *command is a valid function.
 * If it is, returns NO_ERROR, otherwise returns the specific error caught. */
Error checkCommandError(const char *command);

/* Checks if the area in param const char *line between the end index of
 * the parameter in line numbered paramNum with type pType and the index
 * of the next param is valid (comma-wise)
 * Returns NO_ERROR if it's valid, otherwise the specific error that occurs. */
Error checkCommaError(const char *line, param_num paramNum, paramtype pType);

/* Checks if float param number paramNum in const char *line is valid.
 * Returns NO_ERROR if it is, otherwise the specific error caught. */
Error checkParamFloatError(const char *line, ParamNum paramNum);

/* Checks for errors in the param numbered paramNum of const char *line.
 * Returns NO_ERROR if there is no error, otherwise the specific error caught. */
Error checkParamCharError(const char *line, ParamNum paramNum);

/* Checks for illegal extraneous text after the last parameter param lastParam in param const char *line.
 * Returns NO_ERROR if there is no extraneous text, otherwise the specific error caught. */
Error checkExtraneousTextError(const char *line, ParamNum lastParam, paramtype pType);

/* Checks for errors in the stop command.
 * Returns NO_ERROR if there are no errors, otherwise the specific error caught. */
Error checkStopError(const char *line);

/* Returns TRUE if the file ended before the stop command. otherwise FALSE.
 * Param const char *isEof indicates if EOF has been reached, param stopState indicates
 * if the stop command had been sent. */
boolean isEOFBeforeStop(const char *isEof, StopState stopState);

/* Checks if an input line is too long ( > 80).
 * param const char *line is the input line.
 * Returns TRUE if the line is too long, otherwise FALSE. */
boolean isLineTooLong(const char *line);
/* ---------------End of prototypes--------------- */

#endif /* MMN_22_ERROR_CHECK_H */
