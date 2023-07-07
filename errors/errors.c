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

Error handleLineErrors(TransitionNumber_t transitionNumber, ...)
{
    Error error = INPUT_ERROR_CODE;
    va_list ptr;
    va_start(ptr, transitionNumber);

    switch (transitionNumber)
    {
        case PRE_PROCESS:
            error = handlePreProcessErrors(va_arg(ptr, const char *),
                                           va_arg(ptr, NameTable *),
                                           va_arg(ptr, boolean));
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