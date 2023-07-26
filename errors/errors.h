/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * Header file for the errors.c file.
 */

#ifndef MMN_14_ERRORS_H
#define MMN_14_ERRORS_H

/* ---------------Prototypes--------------- */
void printERR(Error error, int lineNumber);
Error handleLineErrors(TransitionNumber_t transitionNumber, const char *line, int lineNumber, ...);
int handle_lineTooLong_error(const char *line, int lineIndex);

/* ---------------------------------------- */

#endif /* MMN_14_ERRORS_H */
