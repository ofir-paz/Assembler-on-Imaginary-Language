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
#include "../../diagnoses/assembler_lang_related_diagnoses.h"
#include "../../diagnoses/diagnose_util.h"
#include "../../general-enums/assemblerFinals.h"
#include "../../util/memoryUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

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