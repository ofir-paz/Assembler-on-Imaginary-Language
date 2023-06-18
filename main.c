/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include "new-data-types/boolean.h"
#include "general-enums/neededFinals.h"
#include "assembler.h"
#include "stdio.h"
/* -------------------------- */

int main(int argc, char *argv[]) {
    int i = ONE_INDEX; /* Loop variable */

    if (argument_error(argc) == TRUE) /* Check for errors with the arguments */
        handle_argument_error(); /* Handle it */

    while (i < argc)
        assemble(argv[i]);

    return 0;
}
