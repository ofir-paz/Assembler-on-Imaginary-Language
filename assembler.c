/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include "new-data-types/process_result.h"
#include "NameTable/NameTable.h"
#include "assembler_ast/assembler_ast.h"
#include "transitions/pre-processor.h"
#include "transitions/first-transition.h"
#include "transitions/second_transition.h"
/* -------------------------- */

/* ---Finals--- */
#define COLOR_GREEN "\x1B[32m"
#define COLOR_RESET "\x1B[0m"
/* ------------ */

/* ---Macros--- */
#define INFO_MSG(message, file) printf("\n" COLOR_GREEN "Assembler state:" COLOR_RESET \
        " %s " COLOR_GREEN "On file:" COLOR_RESET " \"%s\"\n", (message), (file))
/* ------------ */

typedef enum {ASSEMBLER, PRE_PROCESSOR, FIRST_TRANSITION, SECOND_TRANSITION, FINISH} stage_t;

/* ---------------Prototypes--------------- */

void printAssemblerState(const char *file_name, stage_t stageNumber);
void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList);

/* !!! DEBUGGING !!! */
void printData(ast_list_t *astList, NameTable *labelsMap[]);

/* ---------------------------------------- */

void assemble(const char *file_name)
{
    process_result processResult = FAILURE;
    NameTable *labelsMap[TYPES_OF_LABELS] = {NULL};
    ast_list_t *astList = NULL;

    printAssemblerState(file_name, ASSEMBLER);

    //if (handle_filename_error(file_name) == NO_ERROR)
    //{
    printAssemblerState(file_name, PRE_PROCESSOR);
    processResult = pre_process(file_name);
    if (processResult == SUCCESS) {
        printAssemblerState(file_name, FIRST_TRANSITION);
        processResult = first_transition(file_name, labelsMap, &astList);
    }
    if (processResult == SUCCESS) {
        printAssemblerState(file_name, SECOND_TRANSITION);
        processResult = second_transition(file_name, labelsMap, astList);
    }
    //}
    //printData(astList, labelsMap);
    clearDataStructures(labelsMap, &astList);
    printAssemblerState(file_name, FINISH);
}

void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList)
{
    deleteTable(&(labelsMap[NORMAL]));
    deleteTable(&(labelsMap[ENTRY]));
    deleteTable(&(labelsMap[EXTERN]));
    (void) deleteAstList(pAstList);
}

void printAssemblerState(const char *file_name, stage_t stageNumber)
{
    switch (stageNumber)
    {
        case ASSEMBLER:
            INFO_MSG("Starting assembling source assembly file", file_name);
            break;
        case PRE_PROCESSOR:
            INFO_MSG("Starting pre-process stage", file_name);
            break;
        case FIRST_TRANSITION:
            INFO_MSG("Starting first transition stage", file_name);
            break;
        case SECOND_TRANSITION:
            INFO_MSG("Starting second transition stage", file_name);
            break;
        case FINISH:
            INFO_MSG("Finished assembling (due to errors or not)", file_name);
    }
}

/* !!! DEBUGGING !!! */
void printData(ast_list_t *astList, NameTable *labelsMap[])
{
    printAstList(astList);
    printIntTableList(labelsMap);
}