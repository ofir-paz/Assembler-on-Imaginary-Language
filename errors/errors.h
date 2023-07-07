/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * Header file for the errors.c file.
 */

#ifndef MMN_14_ERRORS_H
#define MMN_14_ERRORS_H

/* ---------------Prototypes--------------- */

Error handleLineErrors(TransitionNumber_t transitionNumber, ...);
int handle_lineTooLong_error(const char *line, int lineIndex);

/* ---------------------------------------- */

#endif /* MMN_14_ERRORS_H */
