/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * */

#ifndef MMN_22_DIAGNOSE_INPUT_H
#define MMN_22_DIAGNOSE_INPUT_H

#include "Error.h"
#include "cmd_params.h"
#include "FunctionPtr.h"
#include "paramType.h"

/* ----------Prototypes---------- */

/* Finds the command (function to use) from the input const char *line and
 * sets the param **command to the found command.
 * Returns nothing. */
void findCommand(const char *line, char **command);

/* Finds which handle function param const char *command matches with.
 * Return a pointer to the function, or NULL if it doesn't match with any. */
FunctionPtr getFunction(const char *command);

/* Given the param const char *command and the param Error error,
 * Returns a string contains a suggested fix for the error in the command. */
char *getCmdFix(const char *command, Error error);

/* Finds index of parameter in const char *line.
 * param paramNum specifies the number of parameter to seek.
 * This functions presumes that the command and the commas (up to the parameter to find)
 * are valid since it is supposed to be called after they are validated.
 * Returns the index of the wanted parameter or index of last char ('\0') in line if there isn't. */
int findParamIndex(const char *line, ParamNum paramNum);

/* Finds the length of the parameter number paramNum with type paramtype pType
 * in const char *line.
 * Returns the length of the specific parameter. */
int findParamLen(const char *line, ParamNum paramNum, paramtype pType);

/* Gets the float parameter numbered paramNum from param const char *line.
 * Returns the specified float value. */
float getFloatParamFromLine(const char *line, ParamNum paramNum);

/* Gets the char parameter numbered paramNum from param const char *line.
 * Returns the specified char. */
char getCharParamFromLine(const char *line, ParamNum paramNum);

/* ------------------------------ */

#endif /* MMN_22_DIAGNOSE_INPUT_H */
