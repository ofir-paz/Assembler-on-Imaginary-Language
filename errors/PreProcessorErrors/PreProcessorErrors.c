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
#include "../errors.h"
#include "../error_check.h"
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
        print_assembler_ERR(error, file_name, lineNumber);

    return error; /* Return error */
}

Error getSyntaxPreProcessERR(const char *line, const char *macro_name,
                             boolean wasInMacroDef, boolean isInMacroDef)
{
    Error error = NO_ERROR;

    /* ---Error diagnoses process--- */

    if (isLineTooLong(line))
        error = LINE_OVERFLOW_ERR;
    else if (isInvalidMacroNameERR(macro_name, wasInMacroDef, isInMacroDef) == TRUE)
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
    Error extraneousTextInMacroLine = NO_ERROR; /* Will help to determine value to return. */

    if (isMacroLine(wasInMacroDef, isInMacroDef) == TRUE)
    {
        word_number lastWord = (isInNewMacroDef(wasInMacroDef, isInMacroDef) == TRUE)?
                SECOND_WORD : FIRST_WORD;
        extraneousTextInMacroLine = checkExtraneousTextError(
                line, findStartIndexOfWord(line, lastWord));
    }

    return (extraneousTextInMacroLine != NO_ERROR)? TRUE : FALSE;
}