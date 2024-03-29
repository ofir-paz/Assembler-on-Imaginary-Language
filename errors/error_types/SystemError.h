/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains the new data type 'SystemError' that will be used
 * to distinguish different system errors that can occur.
 */

#ifndef MMN_14_SYSTEMERROR_H
#define MMN_14_SYSTEMERROR_H

/* new SystemError data type.
 * This represents all the system errors that can occur. */
typedef enum
{
    /* Indicates no error, add new errors after this one ! */
        SYSTEM_ERR_START,
    /* Dynamic space allocation errors */
        NO_ALLOCATION_ERR,
    /* File handling related errors */
        FILE_CLOSE_ERR,
    /* Amount of system errors. !! add new errors before this one !! */
        SYSTEM_ERROR_SIZE
} SystemError;

#endif /* MMN_14_SYSTEMERROR_H */
