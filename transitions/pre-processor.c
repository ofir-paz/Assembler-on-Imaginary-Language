/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the methods to write to files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "../errors/error_types/SystemError.h"
#include "../new-data-types/boolean.h"
#include "../new-data-types/process_result.h"
#include "../general-enums/neededFinals.h"
#include "../errors/system_errors.h"
#include "../fileHandling/readFromFile.h"
/* -------------------------- */

/* ---Finals--- */
#define BEFORE_MACRO ".as"
#define AFTER_MACRO ".am"
#define START_MACRO "mcro"
#define END_MACRO "endmcro"
/* ------------ */

/* -----Prototypes----- */
boolean isInMacroDef(const char *line, boolean wasInMacroDef);

void pre_process(const char *file_name)
{
    char *line; /* This will hold the current line */
    boolean inMacroDef = FALSE; /* Flag to indicate if we are inside of a macro definition */

    /* Read the file line-by-line */
    while (readNextLineFromFile(file_name, BEFORE_MACRO, &line) != EOF)
    {
        inMacroDef = isInMacroDef(line, inMacroDef);


    }
}

boolean isInMacroDef(const char *line, boolean wasInMacroDef)
{

}