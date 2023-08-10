/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * Header file for the second_transition.c file.
 */

#ifndef MMN_14_SECOND_TRANSITION_H
#define MMN_14_SECOND_TRANSITION_H

/* ---------------Prototypes--------------- */

/*
 * Main method of second transition stage. will process the created list of
 * ASTs and produce the final product of the assembler.
 *
 * @param   *file_name      The name of the with the assembly source code.
 * @param   *labelsMap[]    Array of tables to hold the different labels.
 * @param   *astList        List of ASTs (Abstract syntax trees) that were made in the
 *                          first transition.
 *
 * @return  SUCCESS on success, FAILURE on failure.
 */
process_result second_transition(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList);

/* ---------------------------------------- */

#endif /* MMN_14_SECOND_TRANSITION_H */
