/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'ImgSystemError' that will be used
 * to distinguish different system errors in the imaginary machine.
 * */

#ifndef MMN_14_IMGSYSTEMERROR_H
#define MMN_14_IMGSYSTEMERROR_H

/* new ImgSystemError data type.
 * This represents all the system errors in the IMAGINARY machine that can occur. */
typedef enum
{
    /* Indicates no error. !! add new errors after this one !! */
        IMG_SYS_ERR_START = start_of_error(0),
    /* Memory limitations errors */
        MEMORY_OVERFLOW_ERR, LINE_OVERFLOW_ERR, NUMBER_TOO_BIG_ERR,
    /* CPU limitations errors */
        UNDEFINED_REGISTER_ERR, NOT_WHOLE_NUMBER,
    /* Amount of imaginary system errors. !! add new errors before this one !! */
        IMG_SYSTEM_ERROR_SIZE
} ImgSystemError;

#endif /* MMN_14_IMGSYSTEMERROR_H */
