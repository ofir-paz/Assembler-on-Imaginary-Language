/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains assembler related finals.
 */

#ifndef MMN_14_ASSEMBLERFINALS_H
#define MMN_14_ASSEMBLERFINALS_H

/* ---Assembler related finals--- */

/* Indicates where the program will be loaded to the memory.
 * Cannot be zero, will produce errors if set to !! */
#define PROGRAM_MEM_START 100

enum {IC_, DC_, COUNTERS_AMOUNT};

#define TWO_QUOTES 2

#define FIRST_LINE 1

#define MAX_LABEL_LEN 31

#define IMG_SYSTEM_MEMORY_SIZE 1024

/* ------------------------------ */

#endif /* MMN_14_ASSEMBLERFINALS_H */
