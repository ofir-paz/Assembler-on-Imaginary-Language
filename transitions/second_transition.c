/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "../new-data-types/process_result.h"
#include "../NameTable/NameTable.h"
#include "../encoding/assembler_ast.h"
#include "../encoding/encoding.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Main method of second transition stage. will process the created list of
 * ASTs and produce the final product of the assembler.
 *
 * @param   *file_name      The name of the with the assembly source code.
 * @param   *labelsMap[]    Array of tables to hold the different labels.
 * @param   *astList        List of ASTs (Abstract syntax trees) that were made in the
 *                          first transition.
 * @param   *memoryImage    The memory image of the assembly code.
 *
 * @return  SUCCESS on success, FAILURE on failure.
 */
process_result second_transition(const char *file_name, NameTable *labelsMap[],
                                 ast_list_t *astList, MemoryImage *memoryImage)
{

}