/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the first_transition_util.c file.
 */

#ifndef MMN_14_FIRST_TRANSITION_UTIL_H
#define MMN_14_FIRST_TRANSITION_UTIL_H

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

/*
 * Adds a label with an associated address to a symbol table during the first transition phase.
 *
 * @param   *labelMap     The symbol table to which the label is added.
 * @param   *labelName    The name of the label to be added.
 * @param   address       The address associated with the label.
 */
void addLabelToTable(NameTable *labelMap, char *labelName, int address);

/*
 * Adds a label to the specified symbol table during the first transition phase.
 *
 * @param   *label       The label to be added.
 * @param   *labelsMap   An array of symbol tables for label management.
 * @param   table        The type of symbol table to add the label to (NORMAL or EXTERN).
 * @param   *argError    Pointer to an error variable for recording the outcome of the operation.
 */
void addLabelToOtherTable(char *label, NameTable *labelsMap[], label_type_t table,
                          Error *argError);

/*
 * Updates one of the give counters IC or DC based on the amount of words
 * needs to encode the line of code represented by lineAst.
 * Assumes that lineAst represents a valid line of code !!
 *
 * @param   *lineAst    The AST representing the line of code.
 * @param   *IC         Instruction counter.
 * @param   *DC         Data counter.
 */
void updateCounters(ast_t *lineAst, int *IC, int *DC);

/* ---------------------------------------- */

#endif /* MMN_14_FIRST_TRANSITION_UTIL_H */
