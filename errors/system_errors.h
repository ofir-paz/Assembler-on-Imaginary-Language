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

/* Handles no allocation error.
 * param void *ptr is the pointer to check if it has allocated space
 * Returns nothing. */
void handle_allocation_error(void *ptr);

/* Handles error with opening a file.
 * param const FILE *file is the stream to check if it has been opened
 * Returns nothing. */
void handle_file_open_errors(const FILE *file);

/* Handles error with closing a file.
 * param int code is the return code of fclose() func.
 * Returns nothing. */
void handle_file_close_errors(int code);

#endif /* MMN_14_SYSTEM_ERRORS_H */
