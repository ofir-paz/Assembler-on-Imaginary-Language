/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * Header file for the pre-processor.c file.
 */

#ifndef MMN_14_PRE_PROCESSOR_H
#define MMN_14_PRE_PROCESSOR_H

#include "../NameTable/NameTable.h"

/* ---------------Prototypes--------------- */

/*
 * Main method of pre-processor stage. will process the file with
 * the given file name.
 *
 * @param   *file_name The name of the file to process.
 * @return  The data structure holding the macros of the .as file.
 */
NameTable *pre_process(const char *file_name);

/* ---------------------------------------- */

#endif /* MMN_14_PRE_PROCESSOR_H */
