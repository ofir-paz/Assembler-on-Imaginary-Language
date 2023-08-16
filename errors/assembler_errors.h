/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * Header file for the errors.c file.
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

int handle_lineTooLong_error(const char *line, int lineIndex);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_ERRORS_H */
