/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * assemblerAlgorithm.c
 *
 * This file implements core algorithms and functions for assembling source code into machine code.
 * It contains the main logic of the assembler, including the processing of lines, translation
 * of instructions and data, symbol resolution, and code generation.
 *
 * The functions within this file contribute to the overall assembly process by applying the
 * algorithmic steps required for converting assembly code to binary machine code. This includes
 * both the first and second transition phases, symbol management, memory image generation, and
 * output file creation.
 *
 * This file plays a central role in the assembler, as it embodies the core logic that transforms
 * the human-readable assembly code into executable machine code for a specific architecture.
 *
 * Note: This implementation assumes the C90 standard for compatibility.
 */

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

/* Assembler stage */
typedef enum {ASSEMBLER, PRE_PROCESSOR, FIRST_TRANSITION, SECOND_TRANSITION, FINISH_FAILURE,
              FINISH_SUCCESS} stage_t;

/* ---------------Prototypes--------------- */
void printAssemblerState(const char *file_name, stage_t stageNumber);
void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList);

/*
---!!! DEBUGGING !!! IGNORE---
void printData(ast_list_t *astList, NameTable *labelsMap[]);
*/

/* ---------------------------------------- */

/*
 * Initiates the assembly process for the given source file.
 *
 * @param   *file_name   The name of the source file to be assembled.
 */
void assemble(const char *file_name)
{
    process_result processResult; /* Will hold every stage process result. */
    NameTable *labelsMap[TYPES_OF_LABELS] = {NULL}; /* Will hold all the labels. */
    ast_list_t *astList = NULL; /* Will hold the diagnosed lines from the first transition. */

    printAssemblerState(file_name, ASSEMBLER); /* Start assembler. */

    printAssemblerState(file_name, PRE_PROCESSOR); /* Start pre-process. */
    processResult = pre_process(file_name);

    if (processResult == SUCCESS)
    {
        printAssemblerState(file_name, FIRST_TRANSITION); /* Start first transition. */
        processResult = first_transition(file_name, labelsMap, &astList);
    }

    if (processResult == SUCCESS)
    {
        printAssemblerState(file_name, SECOND_TRANSITION); /* Start second transition. */
        processResult = second_transition(file_name, labelsMap, astList);
    }

    clearDataStructures(labelsMap, &astList);

    if (processResult == SUCCESS) /* Finished assembling. */
        printAssemblerState(file_name, FINISH_SUCCESS);
    else
        printAssemblerState(file_name, FINISH_FAILURE);
}

/*
 * Clears the data structures used during the assembly process.
 *
 * @param   *labelsMap[]    An array of pointers to symbol tables for label management.
 * @param   **pAstList      Pointer to the list of abstract syntax trees.
 */
void clearDataStructures(NameTable *labelsMap[], ast_list_t **pAstList)
{
    deleteTable(&(labelsMap[NORMAL]));
    deleteTable(&(labelsMap[ENTRY]));
    deleteTable(&(labelsMap[EXTERN]));
    (void) deleteAstList(pAstList);
}

/*
 * Prints the state of the assembler at a specific stage of the assembly process.
 *
 * @param   *file_name   The name of the source file being processed.
 * @param   stageNumber  The stage number indicating the current assembly stage.
 */
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
        case FINISH_FAILURE:
            INFO_MSG("Failed to assemble source file.", file_name);
            break;
        case FINISH_SUCCESS:
            INFO_MSG("Successfully assembled source file!", file_name);
            break;
    }
}

/*
!!! DEBUGGING !!! IGNORE !!!
void printData(ast_list_t *astList, NameTable *labelsMap[])
{
    printAstList(astList);
    printIntTableList(labelsMap);
}

*/