/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains functions to check errors
 * that can occur in the program.
 * This file handles system errors, so if any system error is caught,
 * the program will be terminated !
 * */

#ifndef MMN_14_SYSTEM_ERRORS_H
#define MMN_14_SYSTEM_ERRORS_H

#include <stdio.h>

/* ---------------Prototypes--------------- */

/*
 * Handles no allocation error.
 *
 * @param   *ptr     The pointer to check if it has allocated space.
 */
void handle_allocation_error(void *ptr);

/*
 * Handles error with closing a file.
 *
 * @param   code    The return code of fclose() func.
 */
void handle_file_close_errors(int code);

/* ---------------------------------------- */

#endif /* MMN_14_SYSTEM_ERRORS_H */
