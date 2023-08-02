/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * This file has the method for handling the entire pre-processor stage of the assembler.
 */

/* ---Include header files--- */
#include <stdio.h>
#include "../new-data-types/boolean.h"
#include "../new-data-types/process_result.h"
#include "../NameTable/NameTable.h"
#include "../general-enums/programFinals.h"
#include "../FileHandling/readFromFile.h"
#include "../FileHandling/writeToFile.h"
#include "../errors/PreProcessorErrors/PreProcessorErrors.h"
#include "../diagnoses/diagnose_line.h"
#include "../diagnoses/assembler_lang_related_diagnoses.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Finals--- */
#define BEFORE_MACRO ".as" /* File end of assembly type file */
#define AFTER_MACRO ".am" /* File end of after pre-processor type file */
#define START_MACRO "mcro"
#define END_MACRO "endmcro"
/* ------------ */

/* ----------Prototypes---------- */
process_result traverse_before_macro_file(const char *file_name,
                                          NameTable *amFile, NameTable *macro_table);
Error handleLineInPreProc(const char *file_name, const char *line, char **macro_name,
                          NameTable *amFile, NameTable *macro_table, boolean *wasError);
Error preProcessorAssemblerAlgo(const char *file_name, const char *line, char **macro_name,
                                NameTable *amFile, NameTable *macro_table,
                                int lineCount, boolean *wasError);
boolean isInMcroDef(const char *line, boolean wasInMacroDef);
void getMacroName(const char *line, char **macro_name, boolean wasInMacroDef, boolean isInMacroDef);
void addToTablesIfNeededInPreProc(const char *line, char *macro_name, boolean wasInMacroDef,
                         boolean isInMacroDef, NameTable *amFile, NameTable *macro_table);
char *getMacroIfCalling(const char *line, NameTable *macro_table);
/* ------------------------------ */

/*
 * Main method of pre-processor stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return  The data structure holding the macros of the .as file.
 */
process_result pre_process(const char *file_name)
{
    process_result processResult; /* Value to return. */
    NameTable *amFile = createNameTable(STRING_TYPE); /* Will hold the file to print */
    NameTable *macro_table = createNameTable(STRING_TYPE); /* Will hold the macros */
    (void) addNameToTable(amFile, getDynamicString(AFTER_MACRO));

    processResult = traverse_before_macro_file(file_name, amFile, macro_table);

    /* Create the .am file */
    writeToFile(file_name, AFTER_MACRO,
                (char *) getDataByName(amFile, AFTER_MACRO));

    /* Free unnecessary variable */
    deleteTable(&amFile);
    deleteTable(&macro_table);

    return processResult;
}

/*
 * Traverses the file with the given file name and processes it.
 *
 * @param   *file_name The name of the file to process.
 * @param   *amFile The data structure to hold the contents of the .am file.
 * @param   *macro_table The data structure to hold the macros and their contents.
 */
process_result traverse_before_macro_file(const char *file_name,
                                          NameTable *amFile, NameTable *macro_table)
{
    char *line = NULL; /* This will hold the current line */
    char *macro_name = NULL; /* This will hold the current macro name we are working with. */
    boolean wasError = FALSE;

    /* Read the file line-by-line and handle it. */
    while (readNextLineFromFile(file_name, BEFORE_MACRO, &line) != EOF)
    {
        (void) handleLineInPreProc(file_name, line, &macro_name, amFile, macro_table, &wasError);

        (void) free_ptr(POINTER(line)); /* Next line */
    }

    (void) free_ptr(POINTER(line));
    return (wasError == FALSE)? SUCCESS : FAILURE;
}

/*
 * Handles the given line string in the pre-process.
 *
 * @param   *line Current line string.
 * @param   **macro_name Pointer to the current macro name.
 * @param   *amFile Data structure to hold the file to print.
 * @param   *macro_table Data structure to hold the macro names and contents.
 */
Error handleLineInPreProc(const char *file_name, const char *line, char **macro_name,
                          NameTable *amFile, NameTable *macro_table, boolean *wasError)
{
    static int lineCount = ZERO_COUNT; /* Counter of line */
    Error lineError = NO_ERROR; /* Value to return. Represents the error in the line. */

    lineCount++; /* Increasing line counter by 1 since we reached a new line */

    if (isSkipLine(line) == FALSE) /* Go to next line if we can skip this one */
        lineError = preProcessorAssemblerAlgo(file_name, line, macro_name, amFile, macro_table,
                                              lineCount, wasError);

    return lineError;
}

Error preProcessorAssemblerAlgo(const char *file_name, const char *line, char **macro_name,
                               NameTable *amFile, NameTable *macro_table,
                               int lineCount, boolean *wasError)
{
    static boolean wasInMacroDef = FALSE; /* See if last line was in a mcro def. */

    /* Value to return. Represents the error in the line (if there is). */
    Error lineError = NO_ERROR;

    boolean isInMacroDef = isInMcroDef(line, wasInMacroDef); /* Is curr line in mcro def */
    getMacroName(line, macro_name, wasInMacroDef, isInMacroDef); /* Get curr macro name */

    lineError = handlePreProcessErrors(file_name, line,lineCount, *macro_name,
                                       wasInMacroDef, isInMacroDef);
    if (lineError != NO_ERROR)
        *wasError = TRUE;

    if (lineError == INVALID_MACRO_NAME_ERR) /* Address a specific error */
    {
        isInMacroDef = FALSE;
        (void) free_ptr(POINTER(*macro_name));
    }

    /* Will make the necessary actions. add to amFile, or macro_table */
    addToTablesIfNeededInPreProc(line, *macro_name, wasInMacroDef, isInMacroDef,
                                 amFile, macro_table);

    wasInMacroDef = isInMacroDef;
    return lineError;
}

/*
 * Checks if the given line is inside a macro definition -
 * (has "mcro" at the start or before "endmcro").
 *
 * @param   *line The line to check.
 * @param   wasInMacroDef Flag to indicate of there was already a "mcro" statement.
 * @return  TRUE if line is inside a macro definition, otherwise FALSE.
 */
boolean isInMcroDef(const char *line, boolean wasInMacroDef)
{
    boolean isInMacroDef; /* Value to return */
    char *firstWord = NULL; /* Will hold the first word in the line */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word */

    /* Check if we are in a macro definition. */
    if (wasInMacroDef == FALSE)
        /* Did we enter a new macro definition? */
        isInMacroDef = (sameStrings(firstWord, START_MACRO) == TRUE)? TRUE : FALSE;
    else
        /* Did we exit a macro definition? */
        isInMacroDef = (sameStrings(firstWord, END_MACRO) == TRUE)? FALSE : TRUE;

    (void) free_ptr(POINTER(firstWord)); /* Free unnecessary variable. */
    return isInMacroDef;
}

/*
 * Gets the current macro name the program is working with.
 *
 * @param   *line The line to search for the macro name.
 * @param   **macro_name Pointer to the macro name (will be set to).
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 */
void getMacroName(const char *line, char **macro_name, boolean wasInMacroDef, boolean isInMacroDef)
{
    if (wasInMacroDef == FALSE && isInMacroDef == TRUE) /* Check for start of definition. */
        findWord(line, macro_name, SECOND_WORD); /* Find the macro name */
    else if (isInMacroDef == FALSE) /* Check if the program doesn't handle macros right now. */
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
void addToTablesIfNeededInPreProc(const char *line, char *macro_name, boolean wasInMacroDef,
                         boolean isInMacroDef, NameTable *amFile, NameTable *macro_table)
{
    /* Entered new macro definition, add the macro to the macro table. */
    if (isInNewMacroDef(wasInMacroDef, isInMacroDef) == TRUE)
        (void) addNameToTable(macro_table, macro_name);

    /* Currently defining a macro, add the line to the macro data. */
    else if (isStillInMacroDef(wasInMacroDef, isInMacroDef) == TRUE)
        (void) addStringToData(macro_table, macro_name, line);

    /* End macro statement, Ignore the line. */
    else if (isFinishMacroDef(wasInMacroDef, isInMacroDef) == TRUE);

    /* Check if there is a macro call */
    else if (isCallingMacro(line, macro_table) == TRUE)
    {
        char *macro = getMacroIfCalling(line, macro_table);
        (void) addStringToData(amFile, AFTER_MACRO,
                               getDataByName(macro_table, macro));
        (void) free_ptr(POINTER(macro)); /* Free unnecessary variable. */
    }

    /* Nothing special, Add the current line to .am file. */
    else
        (void) addStringToData(amFile, AFTER_MACRO, line);

}

char *getMacroIfCalling(const char *line, NameTable *macro_table)
{
    char *firstWord = NULL; /* Will hold first word in line. */

    if (isCallingMacro(line, macro_table) == TRUE)
        findWord(line, &firstWord, FIRST_WORD); /* Find the first word. */

    return firstWord;
}