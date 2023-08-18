/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains the new data type 'LogicalError' that will be used
 * to distinguish different logical errors in the program to assemble that can occur.
 */

#ifndef MMN_14_LOGICALERROR_H
#define MMN_14_LOGICALERROR_H

/* new LogicalError data type.
 * This represents all the logical errors that the user can make in the program. */
typedef enum
{
    /* Indicates no error. !! add new errors after this one !! */
        LOGICAL_ERR_START = start_of_error(3),
    /* Macro related logical errors. */

    /* Label related logical errors. */
        MULTIPLE_NORMAL_LABEL_DEF_ERR,

    /* Guidance related logical errors. */
        ARGUMENT_IS_NOT_LABEL_ERR, EXPECTED_NUMBER_ARG_ERR,

    /* Operand related logical errors. */

    /* Addressing methods related logical errors. */
        ILLEGAL_DEST_ARG_MTD_ERR, ILLEGAL_SRC_ARG_MTD_ERR,

    /* Entry label related logical errors */
        MULTIPLE_ENTRY_LABEL_DEF_ERR, ENTRY_LABEL_NOT_DEFINED_IN_FILE_ERR,

    /* Extern label related logical errors */
        MULTIPLE_EXTERN_LABEL_DEF_ERR,

    /* Label tables related logical errors */
        LABEL_DEFINED_AS_NORMAL_AND_EXT_ERR, LABEL_DEFINED_AS_ENT_AND_EXT_ERR,
        USE_OF_UNDEFINED_LABEL_ERR,

    /* Amount of logical errors. !! add new errors before this one !! */
        LOGICAL_ERROR_SIZE
} LogicalError;

#endif /* MMN_14_LOGICALERROR_H */
