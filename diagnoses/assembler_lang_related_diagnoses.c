/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../encoding/encoding-finals/encoding_finals.h"
#include "../general-enums/indexes.h"
#include "diagnose_line.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define NO_SAVED_WORD (-1)
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */


/*
 * Checks if the current line is a "mcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line is a "mcro" statement, otherwise FALSE.
 */
boolean isInNewMacroDef(boolean wasInMacroDef, boolean isInMacroDef)
{
    return (wasInMacroDef == FALSE && isInMacroDef == TRUE)? TRUE : FALSE;
}

/*
 * Checks if the current line and the line before is inside a "mcro" definition.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line and the line before is inside a "mcro" definition,
 *          otherwise FALSE.
 */
boolean isStillInMacroDef(boolean wasInMacroDef, boolean isInMacroDef)
{
    return (wasInMacroDef == TRUE && isInMacroDef == TRUE)? TRUE : FALSE;
}

/*
 * Checks if the current line is an "endmcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE  if the current line is an "endmcro" statement, otherwise FALSE.
 */
boolean isFinishMacroDef(boolean wasInMacroDef, boolean isInMacroDef)
{
    return (wasInMacroDef == TRUE && isInMacroDef == FALSE)? TRUE : FALSE;
}

/*
 * Checks if the given line is calling a macro defined in the specified macro_table.
 *
 * @param   line The line to check if it's calling a macro.
 * @param   macro_table The pointer to the NameTable containing macro names.
 *
 * @return  TRUE if the line is calling a macro, otherwise FALSE.
 */
boolean isCallingMacro(const char *line, NameTable *macro_table)
{
    boolean isCallingMacro; /* Value to return. */
    char *firstWord = NULL; /* Will hold first word in line. */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word. */

    /* Check if a macro has been called. */
    isCallingMacro = isNameInTable(macro_table, firstWord);

    (void) free_ptr(POINTER(firstWord)); /* Free unnecessary variable. */
    return isCallingMacro;
}

/*
 * Checks if the given line is a special macro-related line (not a body of a mcro def).
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line is a macro statement (besides body), otherwise FALSE.
 */
boolean isMacroLine(boolean wasInMacroDef, boolean isInMacroDef)
{
    return (isInNewMacroDef(wasInMacroDef, isInMacroDef) ||
            isFinishMacroDef(wasInMacroDef, isInMacroDef));
}

/*
 * Gets the guidance word that is represented by the given string word.
 *
 * @param   word The given word.
 * @return  The guidance word that is represented by the given string word, or NO_GUIDANCE (-1)
 *          if word is not a guidance word.
 */
guidance_t getGuidance(const char *word)
{
    /* Array to save all the guidance words. */
    const char *guidance_list[] = {".extern", ".entry", ".data", ".string"};
    int sizeOfList = sizeof(guidance_list) / sizeof(guidance_list[ZERO_INDEX]);

    /* Get the index of 'word' in guidance_list. if it's not a guidance word, will be -1. */
    int index = getIndexOfStrInArray(guidance_list, sizeOfList, word);

    return (guidance_t) index;
}

/*
 * Gets the opcode that is represented by the given string word.
 *
 * @param   word The given word.
 * @return  The opcode that is represented by the given string opcode, or NO_OPCODE (-1)
 *          if word is not an opcode.
 */
opcodes_t getOpcode(const char *word)
{
    /* Array to save all the opcodes. */
    const char *opcodes_list[] = {"mov", "cmp", "add", "sub",
                                   "not", "clr", "lea", "inc",
                                   "dec", "jmp", "bne", "red",
                                   "prn", "jsr", "rts", "stop"};
    int sizeOfList = sizeof(opcodes_list) / sizeof(opcodes_list[ZERO_INDEX]);

    /* Get the index of 'word' in opcodes_list. if it's not an opcode, will be -1. */
    int index = getIndexOfStrInArray(opcodes_list, sizeOfList, word);

    return (opcodes_t) index;
}

/*
 * Retrieves the sentence type of the line based on the command at the specified location.
 *
 * @param   *line           The line to check the sentence type of.
 * @param   commandNumber   The location of the command to help determine the sentence type.
 *
 * @return  The sentence type represented by the command.
 */
sentence_type_t getSentenceTypeOfLine(const char *line, word_number commandNumber)
{
    sentence_type_t sentenceType; /* Value to return. */
    char *commandName = NULL; /* Will hold the specific command name. */
    findWord(line, &commandName, commandNumber); /* Find the command name. */

    /* Check which sentence type does the command represents. */
    if (getGuidance(commandName) != NO_GUIDANCE)
        sentenceType = GUIDANCE_SENTENCE;
    else if (getOpcode(commandName) != NO_OPCODE)
        sentenceType = DIRECTION_SENTENCE;
    else /* The command is invalid. */
        sentenceType = NO_TYPE;

    free_ptr(POINTER(commandName)); /* Free unnecessary variable. */
    return sentenceType;
}

/*
 * Checks if the give word is a saved word in the language.
 *
 * @param   word The word to check.
 *
 * @return  TRUE if the word is a saved word, otherwise FALSE.
 */
boolean isSavedWord(const char *word)
{
    return (getGuidance(word) == NO_GUIDANCE && getOpcode(word) == NO_OPCODE)? FALSE : TRUE;
}

/*
 * Retrieves the command at the specified position in the line.
 *
 * @param   line            The input line to retrieve the word from.
 * @param   commandNumber   The position of the command to retrieve in the line.
 *
 * @return  The command at the given position, or -1 if there was no command.
 */
int getCommandFromLine(const char *line, word_number commandNumber)
{
    int command; /* Value to return, represents the command (if there is). */
    char *commandName = NULL; /* Will hold the specific command name. */
    findWord(line, &commandName, commandNumber); /* Find the word. */

    if ((command = getGuidance(commandName)) == NO_GUIDANCE) /* Get the command */
        command = getOpcode(commandName);

    free_ptr(POINTER(commandName)); /* Free unnecessary variable. */
    return command;
}

/*
 * Checks if the word at the specified position in the line matches a saved word.
 *
 * @param   line        The input line to check.
 * @param   wordNumber  The position of the word to check in the line.
 *
 * @return  TRUE if the word at the given position matches a saved word, otherwise FALSE.
 */
boolean isSavedWordInLine(const char *line, word_number wordNumber)
{
    return (getCommandFromLine(line, wordNumber) == NO_SAVED_WORD)? FALSE : TRUE;
}