/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has help methods to assist various other files in this program.
 * */

/* ---Include header files--- */
#include "new-data-types/Error.h"
#include "new-data-types/process_result.h"
#include "NameTable/NameTable.h"
#include "transitions/pre-processor.h"
#include "transitions/first-transition.h"
#include "transitions/second-transition.h"
/* -------------------------- */

void assemble(const char *file_name)
{
    process_result processResult = FAILED;
    NameTable *macro_table;

    //if (handle_filename_error(file_name) == NO_ERROR)
    //{
        macro_table = pre_process(file_name);
    deleteTable(&macro_table);
    //}
}