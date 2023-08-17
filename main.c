/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include "new-data-types/boolean.h"
#include "general-enums/indexes.h"
#include "assembler.h"
/* -------------------------- */

int main(int argc, char *argv[]) {
    int i; /* Loop variable */

    //if (argument_error(argc) == TRUE) /* Check for errors with the arguments */
    //    handle_argument_error(); /* Handle it */

    for (i = ONE_INDEX; i < argc; i++)
        assemble(argv[i]);

    return 0;
}
