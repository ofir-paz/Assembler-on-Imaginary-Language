/*
 * @author Ofir Paz
 * @version (18/8/2023)
 *
 * Header file for the system_errors.c file.
 */

#ifndef MMN_14_SYSTEM_ERRORS_H
#define MMN_14_SYSTEM_ERRORS_H

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
