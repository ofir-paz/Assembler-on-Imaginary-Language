/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/indexes.h"
#include "../general-enums/neededKeys.h"
#include "diagnose_line.h"
#include "diagnose_util.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
#include "../util/numberUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define REG_LEN 3
#define FIRST_REGISTER 0
#define LAST_REGISTER 7
#define NO_SAVED_WORD (-1)
#define COMMA_DELIM ","
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

    (void) clear_ptr(firstWord) /* Free unnecessary variable. */
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
 * Extracts the label from the given line of text.
 *
 * The function searches for the first occurrence of a colon (':') in the line
 * and extracts the label that comes before it. The label is returned as a
 * dynamically allocated C-string (char *) which needs to be freed by the caller
 * when it's no longer needed.
 *
 * @param line      The input line of text to extract the label from.
 *
 * @return          A pointer to the extracted label as a dynamically allocated
 *                  C-string (char *). The function returns NULL if no label is
 *                  found in the line.
 */
char *getLabelFromLine(const char *line)
{
    int start = nextCharIndex(line, MINUS_ONE_INDEX);
    int end = nextSpecificCharIndex(line, start, COLON);

    return strcpyPart(line, start, end);
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
 * Get the register value from the given word.
 *
 * This function checks if the given word represents a register and returns the register value.
 * A register is assumed to be a string of length 2, where the first character is '@' and the
 * second character is 'r', followed by a valid register number ('0' to '7').
 *
 * @param   word        The word to check if it represents a register.
 *
 * @return  register_t  The register value if the word is a valid register, otherwise NO_REGISTER.
 */
reg_t getRegister(const char *word)
{
    reg_t aRegister = NO_REGISTER; /* Register to return, assume word is not a register. */

    /* Finding the register based on the assumption of what a register is in the lang. */
    if (strlen(word) == REG_LEN)
        if (word[ZERO_INDEX] == AT && word[ONE_INDEX] == CHAR_r)
            if (between(word[TWO_INDEX] - CHAR_ZERO, FIRST_REGISTER, LAST_REGISTER)
                == TRUE)
                aRegister = (reg_t) (word[TWO_INDEX] - CHAR_ZERO);

    return aRegister;
}

/*
 * Gets the start index of the command in the given assembly code line.
 *
 * @param   *line       The give line string holding the command.
 * @param   isLabelDef  Flag indicating if the line has a label definition.
 *
 * @return  The start index of the command in the line.
 */
int getCommandStartIndex(const char *line, boolean isLabelDef)
{
    int endIndexOfLabelDef = (isLabelDef == TRUE)?
                             nextSpecificCharIndex(line, ZERO_INDEX, COLON) :
                             MINUS_ONE_INDEX;

    return endIndexOfLabelDef + 1;
}

/*
 * Gets the command from a given line string in a string type.
 *
 * @param   *line           The given line string.
 * @param   isLabelDef      Flag indicating if the line has a label definition.
 *
 * @return  The found command in string type.
 */
char *getCommandStringFromLine(const char *line, boolean isLabelDef)
{
    char *commandName = NULL; /* Will hold the specific command name. */

    /* Find the command name from after the end of the end index of label. */
    findWord(line + getCommandStartIndex(line, isLabelDef), &commandName, FIRST_WORD);

    return commandName;
}

/*
 * Retrieves the command at the specified position in the line.
 *
 * @param   line            The input line to retrieve the word from.
 * @param   isLabelDef      Flag indicating if the line has a label definition.
 *
 * @return  The command at the given position, or -1 if there was no command.
 */
int getCommandFromLine(const char *line, boolean isLabelDef)
{
    int command; /* Value to return, represents the command (if there is). */
    /* Will hold the specific command name. */
    char *commandName = getCommandStringFromLine(line, isLabelDef);

    if ((command = getGuidance(commandName)) == NO_GUIDANCE) /* Get the command */
        command = getOpcode(commandName);

    (void) clear_ptr(commandName) /* Free unnecessary variable. */
    return command;
}

/*
 * Retrieves the sentence type of the line based on the command at the specified location.
 *
 * @param   *line           The line to check the sentence type of.
 * @param   isLabelDef      Flag indicating if the line has a label definition.
 *
 * @return  The sentence type represented by the command.
 */
sentence_type_t getSentenceTypeOfLine(const char *line, boolean isLabelDef)
{
    sentence_type_t sentenceType; /* Value to return. */
    char *commandName = getCommandStringFromLine(line, isLabelDef);

    /* Check which sentence type does the command represents. */
    if (getGuidance(commandName) != NO_GUIDANCE)
        sentenceType = GUIDANCE_SENTENCE;
    else if (getOpcode(commandName) != NO_OPCODE)
        sentenceType = DIRECTION_SENTENCE;
    else /* The command is invalid. */
        sentenceType = NO_SENTENCE_TYPE;

    (void) clear_ptr(commandName) /* Free unnecessary variable. */
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
    return (getGuidance(word) == NO_GUIDANCE && getOpcode(word) == NO_OPCODE &&
            getRegister(word) == NO_REGISTER)? FALSE : TRUE;
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
    boolean isSavedWordInLine; /* Value to return. */
    char *word;
    findWord(line, &word, wordNumber); /* Find the specific word. */

    isSavedWordInLine = isSavedWord(word); /* Check if it's a saved word. */

    (void) clear_ptr(word) /* Free unnecessary variable. */
    return isSavedWordInLine;
}

/*
 * Check if a colon is present in the given assembly code line for a label definition.
 *
 * Will also return TRUE if there is space between the label and the colon,
 * for example: line = "label  : ...". This error needs to be checked !
 *
 * @param   *line   The assembly code line to check for the specific presence of a colon.
 *
 * @return  TRUE if a colon is present for a label definition, otherwise FALSE.
 */
boolean isColonInLineForLabel(const char *line)
{
    int firstColonIndex = nextSpecificCharIndex(line, MINUS_ONE_INDEX, COLON);
    int secondWordIndex = findStartIndexOfWord(line, SECOND_WORD);

    /* Return TRUE if the colon is before or at the start of the second word (if it exists). */
    return (firstColonIndex <= secondWordIndex &&
            line[firstColonIndex] == COLON)? TRUE : FALSE;
}

/*
 * Get the starting index of arguments in the assembly code line.
 *
 * @param   *line       The assembly code line to search for arguments.
 * @param   isLabel     Flag indicating if the line has a label definition.
 *
 * @return  The starting index of the arguments in the line, or index of null terminator of no
 *          arguments are found in the line.
 */
int getStartIndexOfArguments(const char *line, boolean isLabel)
{
    /* Define skip and set it to the start index of the first argument based on the given flag. */
    int skip = (isLabel == TRUE)?
               nextSpecificCharIndex(line, MINUS_ONE_INDEX, COLON) : ZERO_INDEX;
    skip = nextWordIndex(line ,nextCharIndex(line, skip));

    return skip;
}

/*
 * Find the specified argument in the given line.
 *
 * This function tokenizes the line using the delimiter "," and returns
 * the argument at the specified position. If the argument number is out
 * of range or the line is NULL, the function sets *arg to NULL.
 *
 * @param   line        The line containing the arguments.
 * @param   arg         Pointer to a pointer where the argument will be stored.
 * @param   argumentNum The position of the argument to retrieve (starting from 1).
 * @param   isLabel     Flag to indicate if the line has a label definition.
 */
void findArg(const char *line, char **arg, int argumentNum, boolean isLabel)
{
    char *fullArg = NULL;
    int skip = getStartIndexOfArguments(line, isLabel);

    /* Separating by comma. */
    findTokenFromStr(line + skip, &fullArg, argumentNum, COMMA_DELIM);
    /* Clearing the empty space. */
    findWord(fullArg, arg, FIRST_WORD);

    (void) clear_ptr(fullArg)
}

/*
 * Gets the data type of the given argument (in string type).
 * assumes the given string represents a valid argument !!
 *
 * @param   *arg        The given argument in string type.
 * @param   *dataType   Pointer for the argument data.
 */
void getArgDataTypeFromString(char *arg, data_type_t *dataType)
{
    if (isPartOfNumber(arg, ZERO_INDEX) == TRUE) /* Is number */
        *dataType = INT;
    else if (*arg == AT) /* Is register */
        *dataType = REG;
    else /* Otherwise, string. */
        *dataType = STRING;
}

/*
 * Gets the data of the given argument (in string type)
 * assumes the given string represents a valid argument !!
 *
 * @param   *arg        The given argument in string type.
 * @param   *argData    Pointer for the argument data.
 */
void getArgDataFromString(const char *arg, data_t *argData)
{
    switch (argData -> dataType) /* Setting the data based on the type. */
    {
        case INT:
            argData -> data.num = atoi(arg); /* Integer */
            break;
        case STRING:
            argData -> data.string = my_strdup(arg); /* String */
            break;
        case REG:
            argData -> data.reg = getRegister(arg); /* Register */
            break;
    }
}

/*
 * Gets the argument data from a given line string.
 *
 * @param   *line           The line string to get the data from.
 * @param   argumentNum     The number of argument to get the data off.
 * @param   isLabel         Flag indicating if the line has a label definition.
 * @param   *argData        Pointer to store the found data.
 */
void getArgDataFromLine(const char *line, int argumentNum, boolean isLabel, data_t *argData)
{
    char *arg; /* Will hold the argument in string type. */
    findArg(line, &arg, argumentNum, isLabel); /* Find the string containing the argument. */

    getArgDataTypeFromString(arg, &(argData -> dataType)); /* Get the data type. */
    getArgDataFromString(arg, argData); /* Get the data. */

    (void) clear_ptr(arg) /* Free unnecessary variable. */
}

/*
 * Check if the current argument is the last one in the assembly code line.
 *
 * @param   line            The assembly code line to check for the last argument.
 * @param   argumentNum     The current argument number being processed.
 * @param   isLabel         Flag indicating if the line has a label definition.
 *
 * @return  TRUE if the current argument is the last one, FALSE otherwise.
 */
boolean isLastArg(const char *line, int argumentNum, boolean isLabel)
{
    int currArg = getStartIndexOfArguments(line, isLabel);

    while (argumentNum--)
    {
        currArg = nextSpecificCharIndex(line, currArg, COMMA); /* Next comma index. */
        currArg = nextCharIndex(line, currArg); /* Next start of arg index. */
    }

    return (line[currArg] == NULL_TERMINATOR)? TRUE : FALSE;
}