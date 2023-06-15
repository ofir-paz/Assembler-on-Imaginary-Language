//
// Created by ofir on 6/6/23.
//

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "../new-data-types/Error.h"
#include "error_check.h"
#include "error_handle.h"
/* -------------------------- */

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