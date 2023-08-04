/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * Header file for the assembler_lang_related_diagnoses.c file.
 */

#ifndef MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H
#define MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H

#include "../new-data-types/boolean.h"
#include "../NameTable/NameTable.h"
#include "../new-data-types/word_number.h"

/* ---------------Prototypes--------------- */

/* ---Data types prototypes--- */
/* --------------------------- */

/*
 * Checks if the current line is a "mcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line is a "mcro" statement, otherwise FALSE.
 */
boolean isInNewMacroDef(boolean wasInMacroDef, boolean isInMacroDef);

/*
 * Checks if the current line and the line before is inside a "mcro" definition.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line and the line before is inside a "mcro" definition,
 *          otherwise FALSE.
 */
boolean isStillInMacroDef(boolean wasInMacroDef, boolean isInMacroDef);

/*
 * Checks if the current line is an "endmcro" statement.
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line is an "endmcro" statement, otherwise FALSE.
 */
boolean isFinishMacroDef(boolean wasInMacroDef, boolean isInMacroDef);

/*
 * Checks if the given line is calling a macro defined in the specified macro_table.
 *
 * @param   line The line to check if it's calling a macro.
 * @param   macro_table The pointer to the NameTable containing macro names.
 *
 * @return  TRUE if the line is calling a macro, otherwise FALSE.
 */
boolean isCallingMacro(const char *line, NameTable *macro_table);

/*
 * Checks if the given line is a special macro-related line (not a body of a mcro def).
 *
 * @param   wasInMacroDef Flag to indicate if the last line was in a macro definition.
 * @param   inMacroDef Flag to indicate if the current line is in a macro definition.
 *
 * @return  TRUE if the current line is a macro statement (besides body), otherwise FALSE.
 */
boolean isMacroLine(boolean wasInMacroDef, boolean isInMacroDef);

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
register_t getRegister(const char *word);

/*
 * Retrieves the sentence type of the line based on the command at the specified location.
 *
 * @param   *line           The line to check the sentence type of.
 * @param   commandNumber   The location of the command to help determine the sentence type.
 *
 * @return  The sentence type represented by the command.
 */
sentence_type_t getSentenceTypeOfLine(const char *line, word_number commandNumber);

/*
 * Checks of the give word is a saved word in the language.
 *
 * @param   word The word to check.
 *
 * @return  TRUE if the word is a saved word, otherwise FALSE.
 */
boolean isSavedWord(const char *word);

/*
 * Retrieves the command at the specified position in the line.
 *
 * @param   line            The input line to retrieve the word from.
 * @param   commandNumber   The position of the command to retrieve in the line.
 *
 * @return  The command at the given position, or -1 if there was no command.
 */
int getCommandFromLine(const char *line, word_number commandNumber);

/*
 * Checks if the word at the specified position in the line matches a saved word.
 *
 * @param   line        The input line to check.
 * @param   wordNumber  The position of the word to check in the line.
 *
 * @return  TRUE if the word at the given position matches a saved word, otherwise FALSE.
 */
boolean isSavedWordInLine(const char *line, word_number wordNumber);

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
void findArg(const char *line, char **arg, int argumentNum, boolean isLabel);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H */
