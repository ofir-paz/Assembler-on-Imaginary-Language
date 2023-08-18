/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the pre-processor.c file.
 */

#ifndef MMN_14_PRE_PROCESSOR_H
#define MMN_14_PRE_PROCESSOR_H

/* ---------------Prototypes--------------- */

/*
 * Main method of pre-processor stage. will process the file with
 * the given file name.
 *
 * @param   *file_name  The name of the file to process.
 *
 * @return  SUCCESS (1) if there were no errors, otherwise FAILURE (0).
 */
process_result pre_process(const char *file_name);

/* ---------------------------------------- */

#endif /* MMN_14_PRE_PROCESSOR_H */
