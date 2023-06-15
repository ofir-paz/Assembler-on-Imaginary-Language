//
// Created by ofir on 6/5/23.
//

/* ---Include header files--- */
#include <stdio.h>
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "../new-data-types/Error.h"
#include "../new-data-types/process_result.h"
#include "../general-enums/neededFinals.h"
#include "../errors/errors.h"
#include "../fileHandling/readFromFile.h"
/* -------------------------- */

/* ---Finals--- */
#define START_MACRO "mcro"
#define END_MACRO "endmcro"
/* ------------ */

process_result pre_process(const char *file_name)
{
    int currLine = ONE_INDEX;
    boolean isError = FALSE;
    char *line = (char *) malloc(LINE_SIZE); /* This will hold the line string to return */
    handle_malloc_error(line); /* Will handle errors with allocation if there are */

    while (getNextLineFromFile(file_name, &line) != EOF &&
            handle_lineTooLong_error(line, currLine) == NO_ERROR)
    {
        if (handle_preProcessor_error(line, currLine, isInMacro) != NO_ERROR)
            isError = TRUE;
        diag
    }
}

void deleteFileIfError(const char *file_name, Error error)
{
    if (error != NO_ERROR)
    {

    }
}