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
#include "../errors.h"
#include "FirstTransitionSpecificErrorCheck.h"
#include "../../diagnoses/assembler_line_diagnoses.h"
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
SyntaxError checkSyntaxErrorInArg(const char *argument);
SyntaxError checkSyntaxErrorInInstantArg(const char *argument);
SyntaxError checkSyntaxErrorInDirectRegArg(const char *argument);
SyntaxError checkSyntaxErrorInDirectArg(const char *argument);
SyntaxError checkSyntaxErrorBetweenArgs(const char *emptyAfterArgLine);
/* ---------------------------------------- */

void handle_FirstTransLine_Error(const char *file_name, int lineNumber, Error lineError)
{
    print_assembler_ERR(lineError, file_name, lineNumber);
}

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable)
{
    return NO_ERROR;
}

Error checkErrorsInAstFirstTrans(ast_t *lineAst)
{
    return NO_ERROR;
}

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
        guidanceError = UNKNOWN_GUIDANCE_ERR;

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
    SyntaxError operationError; /* Syntax error to return. */

    /* Check if the operation is valid. */
    if (getCommandFromLine(operationLine, FALSE) != NO_OPCODE)
        operationError = NO_ERROR;

    /* Otherwise, find the specific syntax error. */
    else if (isGuidanceButMissingDot(operationLine))
        operationError = MISSING_GUIDANCE_DOT_ERR;
    else if (isDifferentCaseOperation(operationLine))
        operationError = WRONG_CASE_OPERATION_ERR;
    else
        operationError = UNKNOWN_OPERATION_ERR;

    return operationError;
}

/*
 * Checks for a syntax error in the argument and the space between arguments in the given line.
 *
 * @param   *line           The line of assembly code to check for syntax errors.
 * @param   argumentNum     The number of the argument to check for (starting from 1).
 * @param   isLabelDef      Indicates whether the line has a label definition or not.
 *
 * @return  The argument\space syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInArgAndBetween(const char *line, int argumentNum, boolean isLabelDef)
{
    SyntaxError argOrSpaceSyntaxError; /* Syntax error to return. */

    char *arg; /* Will hold the argument. */
    findArg(line, &arg, argumentNum, isLabelDef);

    argOrSpaceSyntaxError = checkSyntaxErrorInArg(arg); /* Get argument errors. */

    if (argOrSpaceSyntaxError == NO_ERROR) /* If found no errors, check errors in the area after. */
    {
        int startIndexOfEmpty = nextEmptyCommaIndex(
                line, getArgumentIndex(line, argumentNum, isLabelDef));

        argOrSpaceSyntaxError = checkSyntaxErrorBetweenArgs(line + startIndexOfEmpty);
    }

    (void) clear_ptr(arg)
    return argOrSpaceSyntaxError;
}

/*
 * Checks for a syntax error in the argument in the given line.
 *
 * @param   *argument   The argument to check for a syntax error in it.
 *
 * @return  The argument syntax error found in the argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInArg(const char *argument)
{
    SyntaxError argumentError; /* Syntax error to return. */

    if (isPartOfNumber(argument, ZERO_INDEX) == TRUE) /* Is number */
        argumentError = checkSyntaxErrorInInstantArg(argument);
    else if (argument[ZERO_INDEX] == AT) /* Is register */
        argumentError = checkSyntaxErrorInDirectRegArg(argument);
    else /* Otherwise, string. */
        argumentError = checkSyntaxErrorInDirectArg(argument);
}

/*
 * Checks for a syntax error between arguments in the given line.
 *
 * @param   *emptyAfterArgLine  The line of assembly code starting in the area after the
 *                              argument to check for a syntax error.
 *
 * @return  The syntax error found in the area after the argument, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorBetweenArgs(const char *emptyAfterArgLine)
{
    SyntaxError areaError;
    int firstCharIndex = nextCharIndex(emptyAfterArgLine, MINUS_ONE_INDEX);

    /* If the last argument was the last one. */
    if (emptyAfterArgLine[firstCharIndex] == NULL_TERMINATOR)
        areaError = NO_ERROR;

    else if (emptyAfterArgLine[firstCharIndex] != COMMA)
        areaError = MISSING_PARAMETER_ERR;

    else if (emptyAfterArgLine[firstCharIndex])
}

SyntaxError checkSyntaxErrorInInstantArg(const char *argument)
{
    SyntaxError instantArgError;

    if (argument[ONE_INDEX] == NULL_TERMINATOR)
        instantArgError = VALUE_IS_ONLY_SIGN_ERR;
    else if (isPlusOrMinus(argument[ONE_INDEX]))
        instantArgError = MULTIPLE_SIGNS_IN_VALUE_ERR;
    else if (isNotInteger(argument))
        instantArgError = INSTANT_VALUE_IS_ILLEGAL_NUMBER;
    else
        instantArgError = NO_ERROR;

    return instantArgError;
}

SyntaxError checkSyntaxErrorInDirectRegArg(const char *argument)
{
    SyntaxError regArgError;

    if (argument[ONE_INDEX] == NULL_TERMINATOR)
        regArgError = EXPECTED_REGISTER_ERR;

    else if (argument[ONE_INDEX] == AT)
        regArgError = MULTIPLE_CONS_AT_ERR;

    else if (isLetter(argument[ONE_INDEX]) == FALSE)
        regArgError = MISSING_REG_LETTER_ERR;

    else if (argument[ONE_INDEX] == CHAR_R)
        regArgError = CAPITAL_REGISTER_LETTER_ERR;

    else if (argument[ONE_INDEX] != CHAR_r)
        regArgError = WRONG_REGISTER_LETTER_ERR;

    else if (isCharNumber(argument[TWO_INDEX]) == FALSE)
        regArgError = EXPECTED_REGISTER_NUMBER_ERR;

    else if (!between(argument[TWO_INDEX] - CHAR_ZERO, r0, r7) ||
                isCharNumber(argument[THREE_INDEX]))
        regArgError = ILLEGAL_REGISTER_NUMBER_ERR;

    else if (argument[THREE_INDEX] != NULL_TERMINATOR)
        regArgError = EXTRANEOUS_TEXT_AFTER_REG_ERR;

    return regArgError;
}

SyntaxError checkSyntaxErrorInDirectArg(const char *argument)
{
    SyntaxError directArgError;

    if (strlen(argument) > MAX_LABEL_LEN)
        directArgError = ARG_LABEL_TOO_LONG_ERR;
    else if (isDirectArgContainsIllegalChars(argument))
        directArgError = ILLEGAL_CHARS_IN_DIRECT_ARG_ERR;

    return directArgError;
}

Error getLogicalErrorInAddToEntryTable(const char *label, NameTable *entLabels,
                                       NameTable *extLabels)
{
    return NO_ERROR;
}

Error getLogicalErrorInAddToExternTable(const char *label, NameTable *labelsMap[])
{
    return NO_ERROR;
}
