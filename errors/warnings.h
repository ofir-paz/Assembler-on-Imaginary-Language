/*
 * @author Ofir Paz
 * @version (17/08/2023)
 *
 * Header file for the warnings.c file.
 */

#ifndef MMN_14_WARNINGS_H
#define MMN_14_WARNINGS_H

/* ---------------Prototypes--------------- */

/* ---Typedef prototype for encapsulation--- */
typedef struct ast_t ast_t;
/* ----------------------------------------- */

/*
 * Handles warnings by finding them if there are, making the necessary changes in the given AST
 * and displaying information about the warning, file name, and line number.
 *
 * @param   *file_name      The name of the file where the warning will be handled (if there is).
 * @param   lineNumber      The line number where the warning will be handled (if there is).
 * @param   *lineAst        The Abstract Syntax Tree (AST) associated with the line.
 */
void handleWarnings(const char *file_name, int lineNumber, ast_t *lineAst);

/* ---------------------------------------- */

#endif /* MMN_14_WARNINGS_H */
