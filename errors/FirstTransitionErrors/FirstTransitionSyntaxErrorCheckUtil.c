/*
 * @author Ofir Paz
 * @version (14/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../../new-data-types/boolean.h"
#include "../../new-data-types/word_number.h"
#include "../../general-enums/neededKeys.h"
#include "../../general-enums/indexes.h"
#include "../../diagnoses/diagnose_line.h"
#include "../../diagnoses/assembler_line_diagnoses.h"
#include "../../diagnoses/assembler_diagnoses.h"
#include "../../diagnoses/diagnose_util.h"
#include "../../general-enums/assemblerFinals.h"
#include "../../util/memoryUtil.h"
#include "../../util/stringsUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/* ---------------LABEL SYNTAX ERRORS--------------- */

/*
 * Checks if a label is missing in the given line.
 * Assuming the line starts with the label definition and that it has a colon in it.
 *
 * @param   *labelLine  The line of assembly code to check for a missing label.
 *
 * @return  TRUE if a label is missing in the given line, otherwise FALSE.
 */
boolean isMissingLabel(const char *labelLine)
{
    return (labelLine[ZERO_INDEX] == COLON)? TRUE : FALSE;
}

/*
 * Checks if there is no empty space between a label and the colon in the given label line.
 *
 * @param   *labelLine  The line of assembly code to check for empty space between label and colon.
 *
 * @return  TRUE if there is empty space between the label and colon, otherwise FALSE.
 */
boolean isEmptyBetweenLabelAndColon(const char *labelLine)
{
    return (nextEmptyIndex(labelLine, ZERO_INDEX) <
            nextSpecificCharIndex(labelLine, ZERO_INDEX, COLON))? TRUE : FALSE;
}

/*
 * Checks if the label in the given label line starts with a number.
 *
 * @param   *labelLine  The line of assembly code to check for a label that starts with a number.
 *
 * @return  TRUE if the label starts with a number, otherwise FALSE.
 */
boolean isLabelStartWithNumber(const char *labelLine)
{
    return isCharNumber(labelLine[ZERO_INDEX]);
}

/*
 * Checks if the label in the given label line starts with an illegal character.
 *
 * @param   *labelLine  The line of assembly code to check for a label that starts with
 *                      an illegal character.
 *
 * @return  TRUE if the label starts with an illegal character, otherwise FALSE.
 */
boolean isLabelStartWithIllegalChar(const char *labelLine)
{
    return (isLetter(labelLine[ZERO_INDEX]) == FALSE)? TRUE : FALSE;
}

/*
 * Checks if the label in the given label line contains any illegal characters.
 *
 * @param   *labelLine  The line of assembly code to check for a label that contains
 *                      illegal characters.
 *
 * @return  TRUE if the label contains illegal characters, otherwise FALSE.
 */
boolean isLabelContainsIllegalChar(const char *labelLine)
{
    boolean isLabelContainsIllegalChar = FALSE; /* Value to return, assume no error. */
    int i = ZERO_INDEX; /* Loop variable. */

    /* While we haven't reached the end of the label definition and didn't find an illegal char. */
    while (labelLine[i] != COLON && isLabelContainsIllegalChar == FALSE)
    {
        if (isLegalChar(labelLine[i]) == FALSE)
            isLabelContainsIllegalChar = TRUE;
        i++;
    }

    return isLabelContainsIllegalChar;
}

/*
 * Checks if the label in the given label line is too long (exceeds the maximum allowed length).
 *
 * @param   *labelLine  The line of assembly code to check for a label that is too long.
 *
 * @return  TRUE if the label is too long, otherwise FALSE.
 */
boolean isLabelTooLong(const char *labelLine)
{
    return (nextSpecificCharIndex(labelLine, ZERO_INDEX, COLON) > MAX_LABEL_LEN)? TRUE : FALSE;
}

/*
 * Checks if the label in the given label line matches a saved word
 * (e.g., an assembler guidance, opcode or register).
 *
 * @param   *labelLine  The line of assembly code to check for a label that matches a saved word.
 *
 * @return  TRUE if the label matches a saved word, otherwise FALSE.
 */
boolean isLabelSavedWord(const char *labelLine)
{
    char *label = getLabelFromLine(labelLine); /* Saving the label in a string. */

    boolean isLabelSavedWord = isSavedWord(label); /* Checking if it's a saved word. */

    (void) clear_ptr(label) /* Freeing the string. */
    return isLabelSavedWord;
}

/*
 * Checks if there are multiple consecutive colons in the given line after the label.
 *
 * @param   *labelLine      The line of assembly code to check for multiple consecutive colons.
 *
 * @return  TRUE if there are multiple consecutive colons after the label in the given line,
 *          otherwise FALSE.
 */
boolean isMultipleConsColons(const char *labelLine)
{
    int colonIndex = nextSpecificCharIndex(labelLine, MINUS_ONE_INDEX, COLON);
    return (labelLine[nextCharIndex(labelLine, colonIndex)] == COLON)? TRUE : FALSE;
}

/*
 * Checks if there is a comma after the label in the given line.
 *
 * @param   *labelLine      The line of assembly code to check for a comma after the label.
 *
 * @return  TRUE if there is a comma after the label in the given line, otherwise FALSE.
 */
boolean isCommaAfterLabel(const char *labelLine)
{
    int colonIndex = nextSpecificCharIndex(labelLine, MINUS_ONE_INDEX, COLON);
    return (labelLine[nextCharIndex(labelLine, colonIndex)] == COMMA)? TRUE : FALSE;
}

/* ---------------END OF LABEL SYNTAX ERRORS--------------- */


/* ---------------GENERAL COMMAND SYNTAX ERRORS--------------- */

/*
 * Checks if the given line is missing an operation or guidance.
 *
 * @param   *commandLine    The line of assembly code to check for missing operation or guidance.
 *
 * @return  TRUE if the given line is missing an operation or guidance, otherwise FALSE.
 */
boolean isMissingOpOrGui(const char *commandLine)
{
    /* If the word that is supposed to be an op or gui starts with illegal char, it's missing. */
    return (!isLetter(commandLine[ZERO_INDEX]) && commandLine[ZERO_INDEX] != DOT)? TRUE : FALSE;
}

/*
 * Checks if there is a comma after the command in the given line.
 *
 * @param   *commandLine    The line of assembly code to check for a comma after the command.
 *
 * @return  TRUE if there is a comma after the command in the given line, otherwise FALSE.
 */
boolean isCommaAfterCmd(const char *commandLine)
{
    int nextComma = nextSpecificCharIndex(commandLine, ZERO_INDEX, COMMA);
    int secondWord = findStartIndexOfWord(commandLine, SECOND_WORD);

    /* Return true if there is a comma after the command before the second word (including). */
    return (commandLine[nextComma] == COMMA && nextComma <= secondWord)? TRUE : FALSE;
}

/* ---------------END OF GENERAL COMMAND SYNTAX ERRORS--------------- */


/* ---------------GUIDANCE SYNTAX ERRORS--------------- */

/*
 * Checks if a guidance is missing in the given line.
 * Assuming the line starts with a dot.
 *
 * @param   *labelLine  The line of assembly code to check for a missing guidance.
 *
 * @return  TRUE if a guidance is missing in the given line, otherwise FALSE.
 */
boolean isMissingGuidance(const char *guidanceLine)
{
    return isEmpty(guidanceLine[ONE_INDEX]);
}

/*
 * Checks if the given line contains multiple consecutive dots in a guidance
 * (if it's valid or not).
 *
 * @param   *guidanceLine   The line of assembly code to check for multiple dots.
 *
 * @return  TRUE if the given line contains guidance with multiple dots, otherwise FALSE.
 */
boolean isMultConsDotsInGuidance(const char *guidanceLine)
{
    return isCurrCharDot(guidanceLine, ONE_INDEX);
}

/*
 * Checks if the given line has a different case guidance.
 *
 * @param   *guidanceLine   The line of assembly code to check for different case guidance.
 *
 * @return  TRUE if the given line has a different case guidance, otherwise FALSE.
 */
boolean isDifferentCaseGuidance(const char *guidanceLine)
{
    boolean isDifferentCaseGuidance = FALSE; /* Value to return, assume false. */
    char *guidance, *lcGuidance; /* Strings to hold the guidance and lower case guidance. */

    findWord(guidanceLine, &guidance, FIRST_WORD); /* Find the word representing the guidance. */
    lcGuidance = strToLowerCase(guidance); /* Turn it to lower case. */

    if (getGuidance(lcGuidance) != NO_GUIDANCE) /* Check if the lower case matches a guidance. */
        isDifferentCaseGuidance = TRUE;

    (void) clear_ptr(guidance) /* Free unnecessary strings. */
    (void) clear_ptr(lcGuidance)
    return isDifferentCaseGuidance;
}

/* ---------------END OF GUIDANCE SYNTAX ERRORS--------------- */


/* ---------------OPERATION SYNTAX ERRORS--------------- */

/*
 * Checks if the given line has a guidance but is missing a dot at the start.
 *
 * @param   *operationLine   The line of assembly code to check for a missing dot in the guidance.
 *
 * @return  TRUE if the given line is a guidance but is missing a dot, otherwise FALSE.
 */
boolean isGuidanceButMissingDot(const char *operationLine)
{
    boolean isGuidanceButMissingDot = FALSE; /* Value to return, assume false. */

    char *guidanceNoDot, *guidance; /* Strings to hold the guidance. */

    findWord(operationLine, &guidanceNoDot, FIRST_WORD);

    /* Connect a dot to see if it's matching a guidance. */
    guidance = connectTwoStrings(".", guidanceNoDot);

    if (getGuidance(guidance) != NO_GUIDANCE) /* Check if it's a guidance but was missing a dot. */
        isGuidanceButMissingDot = TRUE;

    (void) clear_ptr(guidance) /* Free unnecessary strings. */
    (void) clear_ptr(guidanceNoDot)
    return isGuidanceButMissingDot;
}

/*
 * Checks if the given line has a different case operation.
 *
 * @param   *operationLine   The line of assembly code to check for different case operation.
 *
 * @return  TRUE if the given line has a different case operation, otherwise FALSE.
 */
boolean isDifferentCaseOperation(const char *operationLine)
{
    boolean isDifferentCaseOperation = FALSE; /* Value to return, assume false. */
    char *operation, *lcOperation; /* Strings to hold the operation and lower case operation. */

    findWord(operationLine, &operation, FIRST_WORD); /* Find the word representing the operation. */
    lcOperation = strToLowerCase(operation); /* Turn it to lower case. */

    if (getOpcode(lcOperation) != NO_OPCODE) /* Check if the lower case matches a guidance. */
        isDifferentCaseOperation = TRUE;

    (void) clear_ptr(operation) /* Free unnecessary strings. */
    (void) clear_ptr(lcOperation)
    return isDifferentCaseOperation;
}

/*
 * Checks if there is extraneous text after the operation in the given line.
 * Extraneous text after an operation can only be if the operation does not accept arguments.
 * Assumes the given line string starts with an operation.
 *
 * @param   *operationLine  The line of assembly code to check for extraneous text
 *                          after the operation.
 *
 * @return  TRUE if there is extraneous text after the operation in the given line,
 *          otherwise FALSE.
 */
boolean isExtraneousTextAfterOperation(const char *operationLine)
{
    boolean isExtraneousTextAfterOperation = FALSE; /* Value to return. */
    opcodes_t opcode = getCommandFromLine(operationLine, FALSE);

    /* Check for the extraneous text. */
    if (getOpGroup(opcode) == ZERO_ARGS)
        if (operationLine[nextWordIndex(operationLine, ZERO_INDEX)] != NULL_TERMINATOR)
            isExtraneousTextAfterOperation = TRUE;

    return isExtraneousTextAfterOperation;
}

/* ---------------END OF OPERATION SYNTAX ERRORS--------------- */


/* ---------------ARGUMENT SYNTAX ERRORS--------------- */

/*
 * Checks if the given direct argument contains any illegal characters.
 *
 * @param   *directArg  The direct argument (in string type) to check for illegal chars in it.
 *
 * @return  TRUE if the direct argument contains illegal characters, otherwise FALSE.
 */
boolean isDirectArgContainsIllegalChars(const char *directArg)
{
    boolean isDirectArgContainsIllegalChars = FALSE; /* Value to return, assume no error. */
    int i = ZERO_INDEX; /* Loop variable. */

    /* While we haven't reached the end of the direct arg and didn't find an illegal char. */
    while (directArg[i] != NULL_TERMINATOR && isDirectArgContainsIllegalChars == FALSE)
    {
        if (isLegalChar(directArg[i]) == FALSE)
            isDirectArgContainsIllegalChars = TRUE;
        i++;
    }

    return isDirectArgContainsIllegalChars;
}

/* ---------------END OF ARGUMENT SYNTAX ERRORS--------------- */


/* ---------------DIFFERENT AREA SYNTAX ERRORS--------------- */

/*
 * Checks for a syntax error in the given area after the last argument.
 *
 * @param   *area   The area to check for a syntax error.
 *
 * @return  The area syntax error found after the last argument, or NO_ERROR if there isn't.
 */
SyntaxError checkLastArgSyntaxError(const char *area)
{
    SyntaxError lastArgAreaSyntaxError; /* Syntax error to return. */
    int firstCharIndex = nextCharIndex(area, MINUS_ONE_INDEX);

    /* If the last argument was the last one. */
    if (area[firstCharIndex] == NULL_TERMINATOR)
        lastArgAreaSyntaxError = NO_ERROR;

    /* Find the specific syntax error. */
    else if (area[firstCharIndex] == COMMA)
        lastArgAreaSyntaxError = EXTRANEOUS_COMMA_ERR;

    else
        lastArgAreaSyntaxError = EXTRANEOUS_TXT_ERR;

    return lastArgAreaSyntaxError;
}

/*
 * Checks for a syntax error in the area given area that could be after the last
 * argument, or between arguments.
 *
 * @param   *area   The area to check for a syntax error in.
 *
 * @return  The area syntax error found after the last argument or between arguments,
 *          or NO_ERROR if there isn't.
 */
SyntaxError checkAreaOrLastArgSyntaxError(const char *area)
{
    SyntaxError areaOrLastArgSyntaxError; /* Syntax error to return. */
    int chI1 = nextCharIndex(area, MINUS_ONE_INDEX); /* Index of first character in the area. */
    int chI2 = nextCharIndex(area, chI1); /* Index of second character in the area. */

    /* If the last argument was the last one (it can be). */
    if ((area[chI1] == COMMA && area[chI2] != NULL_TERMINATOR && area[chI2] != COMMA) ||
        area[chI1] == NULL_TERMINATOR)
        areaOrLastArgSyntaxError = NO_ERROR;

    /* There is an error, find the specific one. */
    else if (area[chI1] != COMMA)
        areaOrLastArgSyntaxError = EXPECTED_COMMA_OR_EXTRANEOUS_TEXT_ERR;

    /* area[chI1] == COMMA */
    else if (area[chI2] == NULL_TERMINATOR)
        areaOrLastArgSyntaxError = EXPECTED_ARG_OR_EXTRANEOUS_COMMA_ERR;

    /* area[chI2] == COMMA */
    else if (isCharAfterCommas(area, chI2) == TRUE)
        areaOrLastArgSyntaxError = MULTIPLE_CONS_COMMAS_ERR;

    else
        areaOrLastArgSyntaxError = EXTRANEOUS_COMMA_ERR;

    return areaOrLastArgSyntaxError;
}

/*
 * Checks for a syntax error in the given area between arguments.
 *
 * @param   *area   The area to check for a syntax error in.
 *
 * @return  The area syntax error found between arguments, or NO_ERROR if there isn't.
 */
SyntaxError checkAreaArgSyntaxError(const char *area)
{
    SyntaxError areaSyntaxError = NO_ERROR; /* Syntax error to return. */
    int chI1 = nextCharIndex(area, MINUS_ONE_INDEX); /* Index of first character in the area. */

    /* Check for a specific error if there is. */
    if (area[chI1] == NULL_TERMINATOR)
        areaSyntaxError = EXPECTED_COMMA_AND_ARGUMENT_ERR;

    else if (area[chI1] != COMMA)
        areaSyntaxError = EXPECTED_COMMA_ERR;

    else if (isCharAfterCommas(area, chI1) == FALSE)
        areaSyntaxError = EXPECTED_ARGUMENT_ERR;

    else if (area[nextCharIndex(area, chI1)] == COMMA)
        areaSyntaxError = MULTIPLE_CONS_COMMAS_ERR;

    return areaSyntaxError;
}

/* ---------------END OF DIFFERENT AREA SYNTAX ERRORS--------------- */