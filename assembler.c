/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include <stddef.h>
#include "new-data-types/process_result.h"
#include "NameTable/NameTable.h"
#include "encoding/encoding.h"
#include "transitions/pre-processor.h"
#include "transitions/first-transition.h"
#include "transitions/second-transition.h"
/* -------------------------- */

/* ---Finals--- */
/* ------------ */

void assemble(const char *file_name)
{
    process_result processResult = FAILURE;
    NameTable *regLabels = NULL, *entLabels = NULL, *extLabels = NULL;
    MemoryImage *memoryImage = NULL;

    //if (handle_filename_error(file_name) == NO_ERROR)
    //{
    (void) pre_process(file_name);
    //processResult = first_transition(file_name, regLabels, entLabels, extLabels, memoryImage);
    //}

    //(void) clearMemoryImage(memoryImage);
}