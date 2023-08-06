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

void updateDataLabels(NameTable *labels, int finalIC);

/*
 * Build an abstract syntax tree (AST) from the given line of assembly code.
 *
 * @param   line        The line of assembly code to build the AST from.
 * @param   lineError   Pointer to an Error variable that will be set if there are errors
 *                      in the line.
 *
 * @return  Pointer to the root of the AST, or NULL if there was an error during the build process.
 */
ast_t *buildAstFromLine(const char *line, Error *lineError);

void addLabelToTable(NameTable *labelMap, char *labelName, int address);
void addLabelToOtherTable(char *label, NameTable *labelsMap[], label_type_t table,
                          Error *argError);
void updateCounters(ast_t *lineAst, int *IC, int *DC);
/* ---------------------------------------- */

#endif /* MMN_14_FIRST_TRANSITION_UTIL_H */
