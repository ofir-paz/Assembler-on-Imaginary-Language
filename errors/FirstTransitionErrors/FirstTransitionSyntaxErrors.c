/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include "../error_types/error_types.h"
#include "../../NameTable/NameTable.h"
#include "../../assembler_ast/assembler_ast.h"
#include "../../general-enums/indexes.h"
#include "../../general-enums/neededKeys.h"
#include "../../general-enums/assemblerFinals.h"
#include "FirstTransitionSyntaxErrorCheckUtil.h"
#include "../../diagnoses/diagnose_line.h"
#include "../../diagnoses/assembler_line_diagnoses.h"
#include "../../diagnoses/assembler_diagnoses.h"
#include "../../diagnoses/diagnose_util.h"
#include "../../util/memoryUtil.h"
#include "../../util/numberUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
SyntaxError checkSyntaxErrorInGuidance(const char *guidanceLine);
SyntaxError checkSyntaxErrorInOperation(const char *operationLine);
SyntaxError checkSyntaxErrorInArg(const char *argument, boolean isStrGuidance);
SyntaxError checkSyntaxErrorInInstantArg(const char *argument);
SyntaxError checkSyntaxErrorInDirectRegArg(const char *argument);
SyntaxError checkSyntaxErrorInStringArg(const char *argument);
SyntaxError checkSyntaxErrorInDirectArg(const char *argument);
SyntaxError checkSyntaxErrorBetweenArgs(const char *emptyAfterArgLine, area_status_t areaStatus);
/* ---------------------------------------- */

/*
 * Checks for syntax errors in label definition.
 * Assuming there is a colon in the line, and his position is not beyond the start
 * of the second word.
 *
 * @param   *line   The line to check for errors in.
 *
 * @return  The label definition syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInLabel(const char *line)
{
    SyntaxError labelDefError = NO_ERROR; /* Syntax error to return. */
    const char *labelLine = line + nextCharIndex(line, MINUS_ONE_INDEX);

    /* Checking every possible syntax error in the label definition. */
    if (isMissingLabel(labelLine))
        labelDefError = EXPECTED_LABEL_ERR;

    else if (isEmptyBetweenLabelAndColon(labelLine))
        labelDefError = EMPTY_BETWEEN_LABEL_AND_COLON_ERR;

    else if (isLabelStartWithNumber(labelLine))
        labelDefError = LABEL_START_WITH_NUM_ERR;

    else if (isLabelStartWithIllegalChar(labelLine))
        labelDefError = LABEL_START_WITH_ILLEGAL_CHAR_ERR;

    else if (isLabelContainsIllegalChar(labelLine))
        labelDefError = LABEL_CONTAINS_ILLEGAL_CHAR_ERR;

    else if (isLabelTooLong(labelLine))
        labelDefError = LABEL_TOO_LONG_ERR;

    else if (isLabelSavedWord(labelLine))
        labelDefError = LABEL_IS_SAVED_WORD_ERR;

    else if (isMultipleConsColons(labelLine))
        labelDefError = MULTIPLE_CONS_COLONS_ERR;

    else if (isCommaAfterLabel(labelLine))
        labelDefError = COMMA_AFTER_LABEL_ERR;

    return labelDefError;
}

/*
 * Checks for syntax errors in the command of the given line.
 *
 * @param   line        The input line to check for syntax errors in its command.
 * @param   isLabelDef  Flag indicating if the line has a label definition.
 *
 * @return  The command syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInCommand(const char *line, boolean isLabelDef)
{
    SyntaxError commandError = NO_ERROR; /* Syntax error to return, assume no error. */
    const char *commandLine = line + getCommandStartIndex(line, isLabelDef);

    if (isMissingOpOrGui(commandLine)) /* Check if the command is missing. */
        commandError = EXPECTED_OP_GUI_ERR;
    /* Check which type of command to diagnose to error of. */
    else if (isCurrCharDot(commandLine, ZERO_INDEX))
        commandError = checkSyntaxErrorInGuidance(commandLine);
    else
        commandError = checkSyntaxErrorInOperation(commandLine);

    /* Command is valid, check for comma after it. */
    if (commandError == NO_ERROR && isCommaAfterCmd(commandLine) == TRUE)
        commandError = COMMA_AFTER_COMMAND_ERR;

    return commandError;
}

/*
 * Checks for a syntax error in the guidance in the given line with.
 *
 * @param   *guidanceLine   The line of assembly code to check syntax errors in its guidance.
 *
 * @return  The guidance syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInGuidance(const char *guidanceLine)
{
    SyntaxError guidanceError; /* Syntax error to return. */

    /* Check if the guidance is valid. */
    if (getCommandFromLine(guidanceLine, FALSE) != NO_GUIDANCE)
        guidanceError = NO_ERROR;

    /* Otherwise, find the specific syntax error. */
    else if (isMissingGuidance(guidanceLine))
        guidanceError = EXPECTED_GUIDANCE_ERR;
    else if (isMultConsDotsInGuidance(guidanceLine))
        guidanceError = MULT_DOTS_IN_GUIDANCE_ERR;
    else if (isDifferentCaseGuidance(guidanceLine))
        guidanceError = WRONG_CASE_GUIDANCE_ERR;
    else
        guidanceError = UNDEFINED_GUIDANCE_ERR;

    return guidanceError;
}

/*
 * Checks for a syntax error in the operation in the given line.
 *
 * @param   *operationLine   The line of assembly code to check syntax errors in its operation.
 *
 * @return  The operation syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInOperation(const char *operationLine)
{
    SyntaxError operationSyntaxError; /* Syntax error to return. */

    /* Check if the operation is valid. */
    if (getCommandFromLine(operationLine, FALSE) != NO_OPCODE)
        operationSyntaxError = NO_ERROR;

    /* Otherwise, find the specific syntax error. */
    else if (isGuidanceButMissingDot(operationLine))
        operationSyntaxError = MISSING_GUIDANCE_DOT_ERR;
    else if (isDifferentCaseOperation(operationLine))
        operationSyntaxError = WRONG_CASE_OPERATION_ERR;
    else
        operationSyntaxError = UNDEFINED_OPERATION_ERR;

    /* Now if the operation itself is valid, check for extraneous text. */
    if (operationSyntaxError == NO_ERROR)
        if (isExtraneousTextAfterOperation(operationLine))
            operationSyntaxError = EXTRANEOUS_TXT_ERR;

    return operationSyntaxError;
}

/*
 * Checks for a syntax error in the argument and the space between arguments in the given line.
 *
 * @param   *line           The line of assembly code to check for syntax errors.
 * @param   argumentNum     The number of the argument to check for (starting from 1).
 * @param   isLabelDef      Indicates whether the line has a label definition or not.
 * @param   opcode          The opcode of the operation that is in the line
 *                          (NO_OPCODE for guidance).
 * @param   isStrGuidance   Flag indicating if the line has a .string guidance.
 *
 * @return  The argument\space syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInArgAndBetween(const char *line, int argumentNum, boolean isLabelDef,
                                            opcodes_t opcode, boolean isStrGuidance)
{
    SyntaxError argOrSpaceSyntaxError; /* Syntax error to return. */

    char *arg; /* Will hold the argument. */
    findArg(line, &arg, argumentNum, isLabelDef); /* Find the argument. */

    argOrSpaceSyntaxError = checkSyntaxErrorInArg(arg, isStrGuidance); /* Get argument errors. */

    /* If found no errors, check errors in the area after. */
    if (argOrSpaceSyntaxError == NO_ERROR)
    {
        int startIndexOfArea = nextEmptyCommaIndex(
                line, getArgumentIndex(line, argumentNum, isLabelDef));
        area_status_t areaStatus = getAreaStatus(opcode, isStrGuidance, argumentNum);

        argOrSpaceSyntaxError = checkSyntaxErrorBetweenArgs(line + startIndexOfArea, areaStatus);
    }

    (void) clear_ptr(arg) /* Free unnecessary variable. */
    return argOrSpaceSyntaxError;
}

/*
 * Checks for a syntax error in the argument in the given line.
 *
 * @param   *argument   The argument to check for a syntax error in it.
 * @param   isStrGuidance   Flag indicating if the line has a .string guidance.
 *
 * @return  The argument syntax error found in the argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInArg(const char *argument, boolean isStrGuidance)
{
    SyntaxError argumentError; /* Syntax error to return. */

    if (isStrGuidance == TRUE) /* Special case, different argument format. */
        argumentError = checkSyntaxErrorInStringArg(argument);

    else if (isPartOfNumber(argument, ZERO_INDEX) == TRUE) /* Is number */
        argumentError = checkSyntaxErrorInInstantArg(argument);
    else if (argument[ZERO_INDEX] == AT) /* Is register */
        argumentError = checkSyntaxErrorInDirectRegArg(argument);
    else /* Otherwise, label. */
        argumentError = checkSyntaxErrorInDirectArg(argument);

    return argumentError;
}

/*
 * Checks for a syntax error between arguments in the given line.
 *
 * @param   *emptyAfterArgLine  The line of assembly code starting in the area after the
 *                              argument to check for a syntax error.
 * @param   areaStatus          The status of the area after the argument (expecting arg or no).
 *
 * @return  The syntax error found in the area after the argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorBetweenArgs(const char *emptyAfterArgLine, area_status_t areaStatus)
{
    SyntaxError areaSyntaxError; /* Syntax error to return. */

    /* Check the errors based on the status of the area. */
    switch (areaStatus)
    {
        case LAST_ARG:
            areaSyntaxError = checkLastArgSyntaxError(emptyAfterArgLine);
            break;
        case CAN_BE_ANOTHER_ARG:
            areaSyntaxError = checkAreaOrLastArgSyntaxError(emptyAfterArgLine);
            break;
        case MUST_BE_ANOTHER_ARG:
            areaSyntaxError = checkAreaArgSyntaxError(emptyAfterArgLine);
    }

    return areaSyntaxError;
}

/*
 * Checks for a syntax error in the instant argument.
 *
 * @param   *argument   The instant argument (in string type) to check for a syntax error.
 *
 * @return  The specific syntax error in the instant value, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInInstantArg(const char *argument)
{
    SyntaxError instantArgError = NO_ERROR; /* Syntax error to return, assume no error. */

    /* Check for a specific error. */
    if (argument[ONE_INDEX] == NULL_TERMINATOR)
        instantArgError = VALUE_IS_ONLY_SIGN_ERR;

    else if (isPlusOrMinus(argument[ONE_INDEX]))
        instantArgError = MULTIPLE_SIGNS_IN_VALUE_ERR;

    else if (isStrFloat(argument))
        instantArgError = INSTANT_VALUE_IS_FLOAT_ERR;

    else if (isStrInteger(argument) == FALSE)
        instantArgError = INSTANT_VALUE_IS_ILLEGAL_NUMBER_ERR;

    return instantArgError;
}

/*
 * Checks for a syntax error in the direct register argument.
 *
 * @param   *argument   The direct register argument (in string type) to check for a syntax error.
 *
 * @return  The specific syntax error in the direct register argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInDirectRegArg(const char *argument)
{
    SyntaxError regArgSyntaxError = NO_ERROR; /* Syntax error to return, assume no error. */

    /* Check for all the possible errors. */
    if (argument[ONE_INDEX] == NULL_TERMINATOR)
        regArgSyntaxError = EXPECTED_REGISTER_ERR;

    else if (argument[ONE_INDEX] == AT)
        regArgSyntaxError = MULTIPLE_CONS_AT_ERR;

    else if (isLetter(argument[ONE_INDEX]) == FALSE)
        regArgSyntaxError = MISSING_REG_LETTER_ERR;

    else if (argument[ONE_INDEX] == CHAR_R)
        regArgSyntaxError = CAPITAL_REGISTER_LETTER_ERR;

    else if (argument[ONE_INDEX] != CHAR_r)
        regArgSyntaxError = WRONG_REGISTER_LETTER_ERR;

    else if (isCharNumber(argument[TWO_INDEX]) == FALSE)
        regArgSyntaxError = EXPECTED_REGISTER_NUMBER_ERR;

    else if (!between(argument[TWO_INDEX] - CHAR_ZERO, r0, r7) ||
                isCharNumber(argument[THREE_INDEX]))
        regArgSyntaxError = ILLEGAL_REGISTER_NUMBER_ERR;

    else if (argument[THREE_INDEX] != NULL_TERMINATOR)
        regArgSyntaxError = EXTRANEOUS_TEXT_AFTER_REG_ERR;

    return regArgSyntaxError;
}

/*
 * Checks for a syntax error in the string argument
 * (the one that comes after the .string guidance).
 *
 * @param   *argument   The string argument to check for a syntax error.
 *
 * @return  The specific syntax error in the string argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInStringArg(const char *argument)
{
    SyntaxError stringArgSyntaxError = NO_ERROR; /* Syntax error to return, assume no error. */
    int secondQuotesIndex = nextSpecificCharIndex(argument, ZERO_INDEX, QUOTES);

    /* Check all the specific errors. */
    if (argument[ZERO_INDEX] != QUOTES)
        stringArgSyntaxError = MISSING_OPEN_QUOTES_IN_STRING;

    else if (argument[secondQuotesIndex] != QUOTES)
        stringArgSyntaxError = MISSING_CLOSING_QUOTES_IN_STRING;

    else if (argument[secondQuotesIndex + 1] != NULL_TERMINATOR)
        stringArgSyntaxError = EXTRANEOUS_TXT_ERR;

    return stringArgSyntaxError;
}

/*
 * Checks for a syntax error in the direct argument.
 *
 * @param   *argument   The direct argument to check for a syntax error.
 *
 * @return  The specific syntax error in the direct argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInDirectArg(const char *argument)
{
    SyntaxError directArgError = NO_ERROR; /* Syntax error to return, assume no error. */

    /* Check all the specific errors. */
    if (strlen(argument) > MAX_LABEL_LEN)
        directArgError = ARG_LABEL_TOO_LONG_ERR;

    else if (isDirectArgContainsIllegalChars(argument))
        directArgError = ILLEGAL_CHARS_IN_DIRECT_ARG_ERR;

    return directArgError;
}
