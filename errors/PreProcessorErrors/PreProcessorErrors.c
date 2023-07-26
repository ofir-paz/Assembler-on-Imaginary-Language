/*
 * @author Ofir Paz
 * @version (07/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../../new-data-types/boolean.h"
#include "../error_types/error_types.h"
#include "../errors.h"
#include "../../general-enums/indexes.h"
#include "../error_check.h"
#include "../../diagnoses/diagnose_help_methods.h"
#include "../../diagnoses/assembler_lang_related_diagnoses.h"
#include "PreProcessorErrors_help_methods.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
Error getSyntaxPreProcessERR(const char *line, const char *macro_name, boolean isMacroLine);
boolean isInvalidMacroNameERR(const char *macro_name);
boolean isExtraneousTextInMacroLineERR(const char *line, boolean isMacroLine);
/* ---------------------------------------- */

Error handlePreProcessErrors(const char *line, int lineNumber, const char *macro_name,
                             boolean isMacroLine)
{
    Error error = NO_ERROR; /* Value to return. Will represent the found error, or NO_ERROR. */

    /* ---Error diagnoses process--- */

    /* Check for syntax errors */
    error = getSyntaxPreProcessERR(line, macro_name, isMacroLine);

    /* ----------------------------- */

    if (error != NO_ERROR) /* Print error if there is */
        printERR(error, lineNumber);

    return error; /* Return error */
}

Error getSyntaxPreProcessERR(const char *line, const char *macro_name, boolean isMacroLine)
{
    Error error = NO_ERROR;

    /* ---Error diagnoses process--- */

    if (isInvalidMacroNameERR(macro_name) == TRUE)
        error = INVALID_MACRO_NAME_ERR;
    else if (isExtraneousTextInMacroLineERR(line, isMacroLine) == TRUE)
        error = EXTRANEOUS_TEXT_IN_MACRO_LINE_ERR;

    /* ----------------------------- */

    return error;
}

boolean isInvalidMacroNameERR(const char *macro_name)
{
    return isSavedWord(macro_name);
}

boolean isExtraneousTextInMacroLineERR(const char *line, boolean isMacroLine)
{
    Error extraneousTextInMacroLine; /* Will help to determine value to return. */
    int firstWordIndex = nextWordIndex(line, MINUS_ONE_INDEX); /* Index of first word. */

    if (isMacroLine == TRUE)
    {
        if (isFirstWordMcroDef(line) == TRUE)
            extraneousTextInMacroLine =
                    checkExtraneousTextError(
                            line, nextWordIndex(line, firstWordIndex));
        else
            extraneousTextInMacroLine =
                    checkExtraneousTextError(line, firstWordIndex);
    }

    return (extraneousTextInMacroLine != NO_ERROR)? TRUE : FALSE;
}