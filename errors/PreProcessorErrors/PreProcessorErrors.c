/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the functions to check for errors in the pre-processor
 * stage of the assembler.
 */

/* ---Include header files--- */
#include <string.h>
#include "../../new-data-types/boolean.h"
#include "../../new-data-types/word_number.h"
#include "../../general-enums/neededKeys.h"
#include "../error_types/error_types.h"
#include "../../diagnoses/assembler_line_diagnoses.h"
#include "../../diagnoses/diagnose_util.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define MAX_LINE_LEN 80
/* ------------ */

/* ---------------Prototypes--------------- */
boolean isMissingMacroERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef);
boolean isInvalidMacroNameERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef);
boolean isExtraneousTextInMacroLineERR(const char *line,
                                       boolean wasInMacroDef, boolean isInMacroDef);
/* ---------------------------------------- */

/*
 * Checks for errors related to pre-processing during assembly.
 *
 * @param   *line           The input line of assembly code.
 * @param   *macro_name     The name of the macro being defined or used (if applicable).
 * @param   wasInMacroDef   Indicates if the previous line was within a macro definition.
 * @param   isInMacroDef    Indicates if the current line is within a macro definition.
 *
 * @return  An error code indicating the type of pre-processing error,
 *          or NO_ERROR if no error is found.
 */
Error checkPreProcessErrors(const char *line, const char *macro_name,
                            boolean wasInMacroDef, boolean isInMacroDef)
{
    /* Value to return. Will represent the found error, or NO_ERROR. */
    Error macroError = NO_ERROR;

    /* ---Error diagnoses process--- */
    if (isMissingMacroERR(macro_name, wasInMacroDef, isInMacroDef) == TRUE)
        macroError = EXPECTED_MACRO_ERR;

    else if (isInvalidMacroNameERR(macro_name, wasInMacroDef, isInMacroDef) == TRUE)
        macroError = INVALID_MACRO_NAME_ERR;

    else if (isExtraneousTextInMacroLineERR(line, wasInMacroDef, isInMacroDef) == TRUE)
        macroError = EXTRANEOUS_TEXT_IN_MACRO_LINE_ERR;

    /* ----------------------------- */

    return macroError; /* Return error */
}

/*
 * Checks if a given line of text exceeds a specified maximum length.
 * In this assembly language, the maximum line length is 80, not including the new line char.
 *
 * @param   *line   The input line of text to check.
 *
 * @return  TRUE if the line exceeds the maximum length, otherwise FALSE.
 */
boolean isLineTooLong(const char *line)
{
    return (strlen(line) > MAX_LINE_LEN && line[MAX_LINE_LEN] != ENTER_KEY)? TRUE : FALSE;
}

/*
 * Checks if an error related to missing macro definition occurs during assembly.
 *
 * @param   *macro_name     The name of the macro being used.
 * @param   wasInMacroDef   Indicates if the previous line was within a macro definition.
 * @param   isInMacroDef    Indicates if the current line is within a macro definition.
 *
 * @return  TRUE if a missing macro error occurs, otherwise FALSE.
 */
boolean isMissingMacroERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef)
{
    return (isInNewMacroDef(wasInMacroDef, isInMacroDef) && macro_name == NULL)? TRUE : FALSE;
}

/*
 * Checks if an error related to an invalid macro name occurs during assembly.
 *
 * @param   *macro_name     The name of the macro being defined or used.
 * @param   wasInMacroDef   Indicates if the previous line was within a macro definition.
 * @param   isInMacroDef    Indicates if the current line is within a macro definition.
 *
 * @return  TRUE if an invalid macro name error occurs, otherwise FALSE.
 */
boolean isInvalidMacroNameERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef)
{
    return isInNewMacroDef(wasInMacroDef, isInMacroDef) && isSavedWord(macro_name);
}

/*
 * Checks if an error related to extraneous text in a macro line occurs during assembly.
 * A macro line is a line that starts with 'mcro' or 'endmcro'.
 *
 * @param   *line           The input line of assembly code.
 * @param   wasInMacroDef   Indicates if the previous line was within a macro definition.
 * @param   isInMacroDef    Indicates if the current line is within a macro definition.
 *
 * @return  TRUE if an extraneous text in macro line error occurs, otherwise FALSE.
 */
boolean isExtraneousTextInMacroLineERR(const char *line,
                                       boolean wasInMacroDef, boolean isInMacroDef)
{
    Error isExtraTxt = FALSE; /* Value to return. */

    if (isMacroLine(wasInMacroDef, isInMacroDef) == TRUE)
    {
        word_number lastWord = (isInNewMacroDef(wasInMacroDef, isInMacroDef) == TRUE)?
                SECOND_WORD : FIRST_WORD;
        if (line[findStartIndexOfWord(line, lastWord + 1)] != NULL_TERMINATOR)
            isExtraTxt = TRUE;
    }

    return isExtraTxt;
}