/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the assembler_errors.c file.
 */

#ifndef MMN_14_ASSEMBLER_ERRORS_H
#define MMN_14_ASSEMBLER_ERRORS_H

/* ---------------Prototypes--------------- */

/*
 * Handles an assembler error.
 *
 * @param   *file_name      The name of the file where the error occurred.
 * @param   lineNumber      The line number where the error occurred.
 * @param   lineError       The specific error that occurred.
 */
void handle_assembler_error(const char *file_name, int lineNumber, Error lineError);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_ERRORS_H */
