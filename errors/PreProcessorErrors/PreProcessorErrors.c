/*
 * @author Ofir Paz
 * @version (07/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include "../../new-data-types/boolean.h"
#include "../../new-data-types/word_number.h"
#include "../../general-enums/neededKeys.h"
#include "../error_types/error_types.h"
#include "../assembler_errors.h"
#include "../../diagnoses/diagnose_util.h"
#include "../../diagnoses/assembler_line_diagnoses.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define MAX_LINE_LEN 80
/* ------------ */

/* ---------------Prototypes--------------- */
Error getSyntaxPreProcessERR(const char *line, const char *macro_name,
                             boolean wasInMacroDef, boolean isInMacroDef);
boolean isInvalidMacroNameERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef);
boolean isExtraneousTextInMacroLineERR(const char *line,
                                       boolean wasInMacroDef, boolean isInMacroDef);
/* ---------------------------------------- */

Error handlePreProcessErrors(const char *file_name, const char *line, int lineNumber,
                             const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef)
{
    Error error = NO_ERROR; /* Value to return. Will represent the found error, or NO_ERROR. */

    /* ---Error diagnoses process--- */

    /* Check for syntax errors */
    error = getSyntaxPreProcessERR(line, macro_name, wasInMacroDef, isInMacroDef);

    /* ----------------------------- */

    if (error != NO_ERROR) /* Print error if there is */
        handle_assembler_error(file_name, lineNumber, error);

    return error; /* Return error */
}

Error getSyntaxPreProcessERR(const char *line, const char *macro_name,
                             boolean wasInMacroDef, boolean isInMacroDef)
{
    Error error = NO_ERROR;

    /* ---Error diagnoses process--- */

    if (isInvalidMacroNameERR(macro_name, wasInMacroDef, isInMacroDef) == TRUE)
        error = INVALID_MACRO_NAME_ERR;

    else if (isExtraneousTextInMacroLineERR(line, wasInMacroDef, isInMacroDef) == TRUE)
        error = EXTRANEOUS_TEXT_IN_MACRO_LINE_ERR;

    /* ----------------------------- */

    return error;
}

/* Checks if an input line is too long ( > 80).
 * param const char *line is the input line.
 * Returns TRUE if the line is too long, otherwise FALSE. */
boolean isLineTooLong(const char *line)
{
    return (strlen(line) > MAX_LINE_LEN && line[MAX_LINE_LEN] != ENTER_KEY)? TRUE : FALSE;
}

boolean isInvalidMacroNameERR(const char *macro_name, boolean wasInMacroDef, boolean isInMacroDef)
{
    return isInNewMacroDef(wasInMacroDef, isInMacroDef) && isSavedWord(macro_name);
}

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