/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * This file has the method for handling the entire pre-processor stage of the assembler.
 */

/* ---Include header files--- */
#include <stdio.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../general_help_methods.h"
#include "../diagnoses/diagnose_line.h"
#include "../FileHandling/readFromFile.h"
#include "../FileHandling/writeToFile.h"
/* -------------------------- */

/* ---Finals--- */
#define BEFORE_MACRO ".as" /* File end of assembly type file */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
#define START_MACRO "mcro"
#define END_MACRO "endmcro"
/* ------------ */

/* ----------Prototypes---------- */
void traverse_before_macro_file(const char *file_name, NameTable *amFile, NameTable *macro_table);
boolean isInMacroDef(const char *line, boolean wasInMacroDef);
void getMacroName(const char *line, char **macro_name, boolean wasInMacroDef, boolean inMacroDef);
void addToTablesIfNeeded(const char *line, char *macro_name, boolean wasInMacroDef,
                         boolean inMacroDef, NameTable *amFile, NameTable *macro_table);
boolean isInNewMacroDef(boolean wasInMacroDef, boolean inMacroDef);
boolean stillInMacroDef(boolean wasInMacroDef, boolean inMacroDef);
boolean finishMacroDef(boolean wasInMacroDef, boolean inMacroDef);
/* ------------------------------ */

/*
 * Main method of pre-processor stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return  The data structure holding the macros of the .as file.
 */
NameTable *pre_process(const char *file_name)
{
    NameTable *amFile = createNameTable(STRING_TYPE); /* Will hold the file to print */
    NameTable *macro_table = createNameTable(STRING_TYPE); /* Will hold the macros */

    traverse_before_macro_file(file_name, amFile, macro_table);

    /* Create the .am file */
    writeToFile(file_name, AFTER_MACRO,
                getDataByName(amFile, AFTER_MACRO));
    deleteTable(amFile); /* Free unnecessary variable */

    return macro_table;
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
void traverse_before_macro_file(const char *file_name, NameTable *amFile, NameTable *macro_table)
{
    char *line = NULL; /* This will hold the current line */
    char *macro_name = NULL; /* This will hold the current macro name we are working with. */

    /* Flags to indicate the state of macro definition */
    boolean inMacroDef, wasInMacroDef = FALSE;

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, BEFORE_MACRO, &line) != EOF)
    {
        if (isSkipLine(line) == TRUE) continue; /* Go to next line if we can skip this one */
        inMacroDef = isInMacroDef(line, wasInMacroDef); /* See if we're now inside mcro def */
        getMacroName(line, &macro_name, wasInMacroDef, inMacroDef); /* Get curr macro name */

        /* Will make the necessary actions. add to amFile, or macro_table */
        addToTablesIfNeeded(line, macro_name, wasInMacroDef, inMacroDef, amFile, macro_table);

        wasInMacroDef = inMacroDef; /* Next iteration */
    }

    free_ptr(POINTER(line));
}

/*
 * Checks if the given line is inside a macro definition -
 * (has "mcro" at the start or before "endmcro").
 *
 * @param   *line The line to check.
 * @param   wasInMacroDef Flag to indicate of there was already a "mcro" statement.
 * @return  TRUE if line is inside a macro definition, otherwise FALSE.
 */
boolean isInMacroDef(const char *line, boolean wasInMacroDef)
{
    boolean inMacroDef; /* Value to return */
    char *firstWord; /* Will hold the first word in the line */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word */

    /* Check if we are in a macro definition. */
    if (wasInMacroDef == FALSE)
        /* Did we enter a new macro definition? */
        inMacroDef = (sameStrings(firstWord, START_MACRO) == TRUE)? TRUE : FALSE;
    else
        /* Did we exit a macro definition? */
        inMacroDef = (sameStrings(firstWord, END_MACRO) == TRUE)? FALSE : TRUE;

    return inMacroDef;
}

/*
 * Gets the current macro name the program is working with.
 *
 * @param   *line The line to search for the macro name.
 * @param   **macro_name Pointer to the macro name (will be set to).
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 */
void getMacroName(const char *line, char **macro_name, boolean wasInMacroDef, boolean inMacroDef)
{
    if (wasInMacroDef == FALSE && inMacroDef == TRUE) /* Check for start of definition. */
        findWord(line, macro_name, SECOND_WORD); /* Find the macro name */
    else if (inMacroDef == FALSE) /* Check if the program isn't handle macros right now. */
        *macro_name = NULL;
    /* else -- wasInMacroDef == TRUE ** inMacroDef == TRUE -> nothing to do. */
}

/*
 * Adds content to the data structure if needed.
 * Will know if any addition is needed based on the given flags and line string.
 *
 * @param   *line The line string which the program is currently processing.
 * @param   *macro_name The macro name which is the program is currently working with.
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
void addToTablesIfNeeded(const char *line, char *macro_name, boolean wasInMacroDef,
                         boolean inMacroDef, NameTable *amFile, NameTable *macro_table)
{
    char *firstWord; /* Will hold first word in line */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word */

    /* Entered new macro definition, add the macro to the macro table. */
    if (isInNewMacroDef(wasInMacroDef, inMacroDef) == TRUE)
        (void) addNameToTable(macro_table, macro_name);

    /* Currently defining a macro, add the line to the macro data. */
    else if (stillInMacroDef(wasInMacroDef, inMacroDef) == TRUE)
        (void) addStringToData(macro_table, macro_name, line);

    /* End macro statement, Ignore the line. */
    else if (finishMacroDef(wasInMacroDef, inMacroDef) == TRUE);

    /* Check if there is a macro */
    else if (isNameInTable(macro_table, firstWord) == TRUE)
        addStringToData(amFile, AFTER_MACRO,
                        getDataByName(macro_table, firstWord));

    /* Nothing special, Add the current line to .am file. */
    else
        addStringToData(amFile, AFTER_MACRO, line);

    free_ptr(POINTER(firstWord)); /* Free unnecessary pointer */
}

/*
 * Checks if the current line is a "mcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 * @return  TRUE if the current line is a "mcro" statement, otherwise FALSE.
 */
boolean isInNewMacroDef(boolean wasInMacroDef, boolean inMacroDef)
{
    return (wasInMacroDef == FALSE && inMacroDef == TRUE)? TRUE : FALSE;
}

/*
 * Checks if the current line and the line before is inside a "mcro" definition.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 * @return  TRUE if the current line and the line before is inside a "mcro" definition,
 *          otherwise FALSE.
 */
boolean stillInMacroDef(boolean wasInMacroDef, boolean inMacroDef)
{
    return (wasInMacroDef == TRUE && inMacroDef == TRUE)? TRUE : FALSE;
}

/*
 * Checks if the current line is an "endmcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 * @return  TRUE  if the current line is an "endmcro" statement, otherwise FALSE.
 */
boolean finishMacroDef(boolean wasInMacroDef, boolean inMacroDef)
{
    return (wasInMacroDef == TRUE && inMacroDef == FALSE)? TRUE : FALSE;
}