/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the first-transition.c file.
 */

#ifndef MMN_14_FIRST_TRANSITION_H
#define MMN_14_FIRST_TRANSITION_H

/* ---------------Prototypes--------------- */

/*
 * Performs the first transition phase of an assembler on the given source file.
 *
 * @param   *file_name  The name of the source file to be processed.
 * @param   *labelsMap  An array of pointers to symbol tables for label management.
 * @param   **astList   A pointer to the list of abstract syntax trees for line processing.
 *
 * @return  A process_result indicating the outcome of the first transition phase.
 */
process_result first_transition(const char *file_name, NameTable *labelsMap[],
                                ast_list_t **astList);
/* ---------------------------------------- */

#endif /* MMN_14_FIRST_TRANSITION_H */