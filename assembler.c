/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include <stddef.h>
#include "new-data-types/process_result.h"
#include "NameTable/NameTable.h"
#include "assembler_ast/assembler_ast.h"
#include "transitions/pre-processor.h"
#include "transitions/first-transition.h"
#include "transitions/second_transition.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */

/* !!! DEBUGGING !!! */
void printData(ast_list_t *astList, NameTable *labelsMap[]);

void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList);
/* ---------------------------------------- */

void assemble(const char *file_name)
{
    process_result processResult = FAILURE;
    NameTable *labelsMap[TYPES_OF_LABELS] = {NULL};
    ast_list_t *astList = NULL;

    //if (handle_filename_error(file_name) == NO_ERROR)
    //{
    processResult = pre_process(file_name);
    if (processResult == SUCCESS)
        processResult = first_transition(file_name, labelsMap, &astList);
    if (processResult == SUCCESS)
        processResult = second_transition(file_name, labelsMap, astList);
    //}

    //printData(astList, labelsMap);
    clearDataStructures(labelsMap, &astList);
}

void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList)
{
    deleteTable(&(labelsMap[NORMAL]));
    deleteTable(&(labelsMap[ENTRY]));
    deleteTable(&(labelsMap[EXTERN]));
    (void) deleteAstList(pAstList);
}

/* !!! DEBUGGING !!! */
void printData(ast_list_t *astList, NameTable *labelsMap[])
{
    printAstList(astList);
    printIntTableList(labelsMap);
}