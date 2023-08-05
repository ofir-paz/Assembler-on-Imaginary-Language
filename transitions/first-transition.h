/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * Header file for the first-transition.c file.
 */

#ifndef MMN_14_FIRST_TRANSITION_H
#define MMN_14_FIRST_TRANSITION_H

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */

/*
 * Main method of first transition stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return
 */
process_result first_transition(const char *file_name, NameTable *labelsMap[],
                                ast_list_t **astList);
/* ---------------------------------------- */

#endif /* MMN_14_FIRST_TRANSITION_H */