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
#include "../../diagnoses/assembler_line_diagnoses.h"
#include "../../diagnoses/diagnose_line.h"
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
    boolean isLabelIContainsIllegalChar = FALSE; /* Value to return, assume no error. */
    int i = ZERO_INDEX; /* Loop variable. */

    /* While we haven't reached the end of the label definition and didn't find an illegal char. */
    while (labelLine[i] != COLON && isLabelIContainsIllegalChar == FALSE)
    {
        if (isLegalChar(labelLine[i]) == FALSE)
            isLabelIContainsIllegalChar = TRUE;
        i++;
    }

    return isLabelIContainsIllegalChar;
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

/* ---------------END OF OPERATION SYNTAX ERRORS--------------- */