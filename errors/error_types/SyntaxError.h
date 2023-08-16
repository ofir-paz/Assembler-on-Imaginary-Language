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
        LABEL_TOO_LONG_ERR, LABEL_IS_SAVED_WORD_ERR, MULTIPLE_CONS_COLONS_ERR,
        COMMA_AFTER_LABEL_ERR,

    /* Command syntax errors */
        EXPECTED_OP_GUI_ERR, COMMA_AFTER_COMMAND_ERR,

    /* Guidance syntax errors. */
        EXPECTED_GUIDANCE_ERR, MULT_DOTS_IN_GUIDANCE_ERR, WRONG_CASE_GUIDANCE_ERR,
        UNDEFINED_GUIDANCE_ERR,

    /* Operation syntax errors. */
        MISSING_GUIDANCE_DOT_ERR, WRONG_CASE_OPERATION_ERR, UNDEFINED_OPERATION_ERR,

    /* General argument errors. */
        EXPECTED_COMMA_AND_ARGUMENT_ERR, EXPECTED_COMMA_ERR, EXPECTED_ARGUMENT_ERR,
        MULTIPLE_CONS_COMMAS_ERR,

    /* String argument syntax errors. */
        MISSING_OPEN_QUOTES_IN_STRING, MISSING_CLOSING_QUOTES_IN_STRING,

    /* Instant value argument syntax errors. */
        VALUE_IS_ONLY_SIGN_ERR, MULTIPLE_SIGNS_IN_VALUE_ERR, INSTANT_VALUE_IS_FLOAT_ERR,
        INSTANT_VALUE_IS_ILLEGAL_NUMBER_ERR,

    /* Label argument syntax errors. */
        ARG_LABEL_TOO_LONG_ERR, ILLEGAL_CHARS_IN_DIRECT_ARG_ERR,

    /* Register argument syntax errors.*/
        EXPECTED_REGISTER_ERR, MULTIPLE_CONS_AT_ERR, MISSING_REG_LETTER_ERR,
        CAPITAL_REGISTER_LETTER_ERR, WRONG_REGISTER_LETTER_ERR, EXPECTED_REGISTER_NUMBER_ERR,
        ILLEGAL_REGISTER_NUMBER_ERR, EXTRANEOUS_TEXT_AFTER_REG_ERR,

    /* Extraneous text errors */
        EXTRANEOUS_COMMA_ERR, EXTRANEOUS_TXT_ERR, EXPECTED_COMMA_OR_EXTRANEOUS_TEXT_ERR,
        EXPECTED_ARG_OR_EXTRANEOUS_COMMA_ERR,

    /* Amount of syntax errors. !! add new errors before this one !! */
        SYNTAX_ERROR_SIZE
} SyntaxError;

#endif /* MMN_14_SYNTAXERROR_H */
