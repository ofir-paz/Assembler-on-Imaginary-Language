/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'Error'.
 * */

#ifndef MMN_14_ERROR_H
#define MMN_14_ERROR_H

/* New data type Error.
 * This represents all the errors that can occur in the program.
 * !! To add an error, you must add it before NO_ERROR !! */
typedef enum {
    /* System errors */
                NO_SPACE_IN_MEM,
    /* Function input error */
                WRONG_CASE_FUNC, UNDEFINED_FUNC, COMMA_AFTER_CMD,
    /* Comma input error */
                NO_COMMA, CONSEC_COMMAS,
    /* Float param input error */
              NO_FLOAT_PARAM, ONLY_SIGN, NOT_A_FLOAT, TOO_MANY_DOTS,
    /* Char param input error */
              NO_CHAR_PARAM, NOT_ONE_CHAR, NOT_LETTER, NOT_CAPITAL, UNDEFINED_C_VAR,
    /* Extraneous text errors */
              EXTRANEOUS_COMMA, EXTRANEOUS_TXT,
    /* More errors */
              EOF_BEFORE_STOP, GENERAL_ERR,
              LINE_TOO_LONG,
    /* !! Add new errors before this one !! */
              NO_ERROR} Error;

#endif /* MMN_14_ERROR_H */