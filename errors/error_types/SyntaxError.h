/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains the new data type 'SyntaxError' that will be used
 * to distinguish different syntax errors in the input file.
 * */

#ifndef MMN_14_SYNTAXERROR_H
#define MMN_14_SYNTAXERROR_H

/* new SyntaxError data type.
 * This represents all the syntax error that the user can make. */
typedef enum
{
    /* Indicates no error. !! add new errors after this one !! */
        SYNTAX_ERR_START = start_of_error(2),
    /* Macro related syntax errors */
        INVALID_MACRO_NAME_ERR, EXTRANEOUS_TEXT_IN_MACRO_LINE_ERR,
    /* Label related syntax errors */
        EXPECTED_LABEL_ERR, EMPTY_BETWEEN_LABEL_AND_COLON_ERR, LABEL_START_WITH_NUM_ERR,
        LABEL_START_WITH_ILLEGAL_CHAR_ERR, LABEL_CONTAINS_ILLEGAL_CHAR_ERR,
        LABEL_TOO_LONG_ERR, LABEL_IS_SAVED_WORD_ERR,
    /* Command syntax errors */
        EXPECTED_OP_GUI_ERR, COMMA_AFTER_COMMAND_ERR,
    /* Guidance syntax errors. */
        EXPECTED_GUIDANCE_ERR, MULT_DOTS_IN_GUIDANCE_ERR, WRONG_CASE_GUIDANCE_ERR,
        UNKNOWN_GUIDANCE_ERR,
    /* Operation syntax errors. */
        MISSING_GUIDANCE_DOT_ERR, WRONG_CASE_OPERATION_ERR, UNKNOWN_OPERATION_ERR,
    /* Comma syntax errors */
        COMMA_AFTER_OP_ERR, NO_COMMA_ERR, CONSEC_COMMAS_ERR,
    /* Extraneous text errors */
        EXTRANEOUS_COMMA_ERR, EXTRANEOUS_TXT_ERR,
    /* Amount of syntax errors. !! add new errors before this one !! */
        SYNTAX_ERROR_SIZE
} SyntaxError;

#endif /* MMN_14_SYNTAXERROR_H */
