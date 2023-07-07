/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'LogicalError' that will be used
 * to distinguish different logical errors in the program to assemble that can occur.
 * */

#ifndef MMN_14_LOGICALERROR_H
#define MMN_14_LOGICALERROR_H

/* new LogicalError data type.
 * This represents all the logical errors that the user can make in the program. */
typedef enum
{
    /* Indicates no error. !! add new errors after this one !! */
        LOGICAL_ERR_START = start_of_error(3),
    /* Macro related logical errors */
        MCRO_BEFORE_DEF_ERR,
    /* Label related logical errors */
        LABEL_NAME_IS_OP, MULT_LABEL_DEF_ERR, EMPTY_LABEL,
    /* Extern label related logical errors */

    /* Entry label related logical errors */

    /* Operands logical errors */
        UNDEFINED_LABEL_ERR,
    /* Wrong addressing method errors */
        FIRST_OPERAND_ADDRESSING_ERR, SECOND_OPERAND_ADDRESSING_ERR,
    /* Amount of logical errors. !! add new errors before this one !! */
        LOGICAL_ERROR_SIZE
} LogicalError;

#endif /* MMN_14_LOGICALERROR_H */
