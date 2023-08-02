/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * Header file for the first_transition_util.c file.
 */

#ifndef MMN_14_FIRST_TRANSITION_UTIL_H
#define MMN_14_FIRST_TRANSITION_UTIL_H

#include "../encoding/assembler_ast.h"

/* ---------------Prototypes--------------- */
ast_t *buildAstFromLine(const char *line, NameTable *labelsMap[], Error *lineError);
void updateCounters(ast_t *lineAst, int *IC, int *DC);
void handleFirstTransLineError(const char *file_name, int lineCount, Error lineError,
                               boolean *wasError);
/* ---------------------------------------- */

#endif /* MMN_14_FIRST_TRANSITION_UTIL_H */
