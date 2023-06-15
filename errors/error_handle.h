/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the error_handle.c file
 * */

#ifndef MMN_22_ERROR_HANDLE_H
#define MMN_22_ERROR_HANDLE_H

#include "Error.h"

typedef struct complex complex; /* Prototype for complex data type */

/* ----------Prototypes---------- */

/* Handles the error where there has been a failed allocation in the memory.
 * Returns nothing. */
void noAllocationERR();

/* Handles an invalid command with the given param Error cmdERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidCommand(Error cmdERR, char **fix);

/* Handles invalid commas with the given param Error commaERR to indicate the error.
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidCommas(Error commaERR, char **fix);

/* Handles invalid param with the given param Error paramERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleInvalidParam(Error paramERR, char **fix);

/* Handles the extraneous text error by the given param Error extraERR to indicate the error,
 * and param char **fix to indicate the fix for the error if there is (a fix).
 * Returns nothing. */
void handleExtraneousERR(Error extraERR, char **fix);

void handle_lineTooLong_ERR(int lineIndex);

/* ------------------------------ */

#endif /* MMN_22_ERROR_HANDLE_H */
