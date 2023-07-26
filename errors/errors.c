/*
 * @author Ofir Paz
 * @version (28/06/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdarg.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../transitions/TransitionNumber.h"
#include "error_types/error_types.h"
#include "PreProcessorErrors/PreProcessorErrors.h"
#include "error_check.h"
#include "error_handle.h"
/* -------------------------- */

/* ---Finals--- */
#define INPUT_ERROR_CODE (-1)
/* ------------ */

void printERR(Error error, int lineNumber)
{
    const char *imgSystemErrorMSG[] =
            {
                "NO_ERROR",
                ""
            };
    const char *syntaxErrorMSG[] =
            {
                    "NO_ERROR",
                    ""
            };
    const char *logicalErrorMSG[] =
            {
                    "NO_ERROR",
                    ""
            };

}

Error handleLineErrors(TransitionNumber_t transitionNumber, const char *line, int lineNumber, ...)
{
    Error error = INPUT_ERROR_CODE;
    va_list ptr;
    va_start(ptr, lineNumber);

    switch (transitionNumber)
    {
        case PRE_PROCESS:
            error = handlePreProcessErrors(line, lineNumber,
                                           va_arg(ptr, const char *), /* macro_name= */
                                           va_arg(ptr, boolean)); /* isMacroLine= */
            break;
        case FIRST_TRANSITION:
            break;
        case SECOND_TRANSITION:
            break;
    }
    va_end(ptr);
    return error;
}

Error handle_lineTooLong_error(const char *line, int lineIndex)
{
    Error error = NO_ERROR;

    if (isLineTooLong(line) == TRUE)
    {
        handle_lineTooLong_ERR(lineIndex);
        error = LINE_TOO_LONG;
    }

    return error;
}