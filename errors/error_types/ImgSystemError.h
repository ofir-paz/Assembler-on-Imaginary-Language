/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains the new data type 'ImgSystemError' that will be used
 * to distinguish different system errors in the imaginary machine.
 */

#ifndef MMN_14_IMGSYSTEMERROR_H
#define MMN_14_IMGSYSTEMERROR_H

/* new ImgSystemError data type.
 * This represents all the system errors in the IMAGINARY machine that can occur. */
typedef enum
{
    /* Indicates no error. !! add new errors after this one !! */
        IMG_SYSTEM_ERR_START = start_of_error(1),

    /* Memory limitations errors */
        LINE_OVERFLOW_ERR, INSTANT_VALUE_OVERFLOW_ERR, DATA_VALUE_OVERFLOW_ERR,
        PROG_MEM_OVERFLOW_ERR,

    /* CPU limitations errors */

    /* Amount of imaginary system errors. !! add new errors before this one !! */
        IMG_SYSTEM_ERROR_SIZE
} ImgSystemError;

#endif /* MMN_14_IMGSYSTEMERROR_H */
