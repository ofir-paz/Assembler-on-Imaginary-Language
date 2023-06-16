/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'SystemError' that will be used
 * to distinguish different system errors that can occur.
 * */

#ifndef MMN_14_SYSTEMERROR_H
#define MMN_14_SYSTEMERROR_H

/* new SystemError data type */
typedef enum {NO_ERROR, /* Indicates no error, add new errors after this one ! */
              NO_ALLOCATION_ERR, /* Dynamic space allocation errors */
              FILE_OPEN_ERR, FILE_CLOSE_ERR,  /* File handling related errors */
              SYSTEM_ERROR_SIZE /* Amount of system errors. add new errors before this one ! */
} SystemError;

#endif /* MMN_14_SYSTEMERROR_H */
