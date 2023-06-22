/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the methods to write to files.
 * */

/* ---Include header files--- */
#include <stdio.h>
#include "../errors/error_types/SystemError.h"
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../new-data-types/process_result.h"
#include "../general-enums/indexes.h"
#include "../errors/system_errors.h"
#include "../general_help_methods.h"
#include "../diagnoses/diagnose_line.h"
#include "../FileHandling/readFromFile.h"
#include "../FileHandling/writeToFile.h"
/* -------------------------- */

/* ---Finals--- */
#define BEFORE_MACRO ".as"
#define AFTER_MACRO ".am"
#define START_MACRO "mcro"
#define END_MACRO "endmcro"
/* ------------ */

/* ----------Prototypes---------- */
void traverse_before_macro_file(const char *file_name, NameTable *amFile, NameTable *macro_table);
boolean isInMacroDef(const char *line, boolean wasInMacroDef);
/* ------------------------------ */

NameTable *pre_process(const char *file_name)
{
    NameTable *amFile = createNameTable(STRING_TYPE); /* Will hold the file to print */
    NameTable *macro_table = createNameTable(STRING_TYPE); /* Will hold the macros */

    traverse_before_macro_file(file_name, amFile, macro_table);

    /* Create the .am file */
    writeToFile(file_name, AFTER_MACRO, getDataByName(amFile, AFTER_MACRO));
    deleteTable(amFile); /* Free unnecessary variable */

    return macro_table;
}

void traverse_before_macro_file(const char *file_name, NameTable *amFile, NameTable *macro_table)
{
    char *line; /* This will hold the current line */
    boolean inMacroDef = FALSE; /* Flag to indicate if we are inside of a macro definition */

    /* Read the file line-by-line */
    while (readNextLineFromFile(file_name, BEFORE_MACRO, &line) != EOF)
    {
        if (isSkipLine(line) == TRUE) continue; /* Go to next line if we can skip this one */
        inMacroDef = isInMacroDef(line, inMacroDef);

    }
}

boolean isInMacroDef(const char *line, boolean wasInMacroDef)
{
    boolean inMacroDef; /* Value to return */
    char *firstWord; /* Will hold the first word in the line */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word */
    if (wasInMacroDef == FALSE) /* Check for mcro */
    {
        inMacroDef = (sameStrings(firstWord, START_MACRO) == TRUE)? TRUE : FALSE;
    }
}