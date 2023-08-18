/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * assembler.c
 *
 * This file houses the main function of the assembler program, orchestrating the complete
 * assembly process. The assembler takes source code written in assembly language and
 * transforms it into executable machine code for a specific target architecture.
 *
 * The main function in this file serves as the entry point for the assembler program. It
 * handles command-line arguments, file processing, and manages the different phases of the
 * assembly process. This includes the first and second transition phases, as well as the
 * handling of errors, warnings, and the generation of output files.
 *
 * The assembler program integrates various modules, such as the lexical analyzer, parser,
 * symbol table management, and code generation, to create a seamless assembly experience.
 * It provides feedback on potential issues in the source code and produces the final
 * machine code in Base64 format.
 *
 * Note: This implementation assumes the C90 standard for compatibility.
 *
 * This project was made by Ofir Paz for the open university of israel.
 * The project was made through the scope of the course 'Systems Programming Lab' as
 * the final project.
 */

/* ---Include header files--- */
#include <stdio.h>
#include "assembler_algorithm.h"
/* -------------------------- */

/* ---Finals--- */
#define NO_GIVEN_FILES 1
#define FIRST_FILE_NAME 1
#define SUCCESS_CODE 0
/* ------------ */

/*
 * Driver code.
 */
int main(int argc, char *argv[])
{
    int i; /* Loop variable */

    if (argc == NO_GIVEN_FILES) /* Print a message if the arguments are insufficient. */
        puts("\nPlease select the assembly source files to assemble.");

    for (i = FIRST_FILE_NAME; i < argc; i++) /* Assemble all the files. */
        assemble(argv[i]);

    return SUCCESS_CODE;
}
