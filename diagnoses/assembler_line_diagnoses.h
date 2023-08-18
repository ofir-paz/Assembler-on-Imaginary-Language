/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the assembler_lang_related_diagnoses.c file.
 */

#ifndef MMN_14_ASSEMBLER_LINE_DIAGNOSES_H
#define MMN_14_ASSEMBLER_LINE_DIAGNOSES_H

/* Include very basic data types. */
#include "../new-data-types/boolean.h"
#include "../new-data-types/word_number.h"
#include "../assembler_ast/assembler_ast.h"

/* ---------------Prototypes--------------- */

/* ---Data types prototypes--- */
typedef struct NameTable NameTable;
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
char *getLabelFromLine(const char *line);

/*
 * Gets the guidance word that is represented by the given string word.
 *
 * @param   word The given word.
 * @return  The guidance word that is represented by the given string word, or NO_GUIDANCE (-1)
 *          if word is not a guidance word.
 */
guidance_t getGuidance(const char *word);

/*
 * Gets the opcode that is represented by the given string word.
 *
 * @param   word The given word.
 * @return  The opcode that is represented by the given string opcode, or NO_OPCODE (-1)
 *          if word is not an opcode.
 */
opcodes_t getOpcode(const char *word);

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
reg_t getRegister(const char *word);

/*
 * Gets the start index of the command in the given assembly code line.
 *
 * @param   *line       The give line string holding the command.
 * @param   isLabelDef  Flag indicating if the line has a label definition.
 *
 * @return  The start index of the command in the line.
 */
int getCommandStartIndex(const char *line, boolean isLabelDef);

/*
 * Retrieves the command at the specified position in the line.
 *
 * @param   line            The input line to retrieve the word from.
 * @param   isLabelDef      Flag indicating if the line has a label definition.
 *
 * @return  The command at the given position, or -1 if there was no command.
 */
int getCommandFromLine(const char *line, boolean isLabelDef);

/*
 * Retrieves the sentence type of the line based on the command at the specified location.
 *
 * @param   *line           The line to check the sentence type of.
 * @param   isLabelDef      Flag indicating if the line has a label definition.
 *
 * @return  The sentence type represented by the command.
 */
sentence_type_t getSentenceTypeOfLine(const char *line, boolean isLabelDef);

/*
 * Checks of the give word is a saved word in the language.
 *
 * @param   word The word to check.
 *
 * @return  TRUE if the word is a saved word, otherwise FALSE.
 */
boolean isSavedWord(const char *word);

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
 * Check if a colon is present in the given assembly code line for a label definition.
 *
 * Will also return TRUE if there is space between the label and the colon,
 * for example: line = "label  : ...". This error needs to be checked !
 *
 * @param   *line   The assembly code line to check for the specific presence of a colon.
 *
 * @return  TRUE if a colon is present for a label definition, otherwise FALSE.
 */
boolean isColonInLineForLabel(const char *line);

/*
 * Gets the index of the specified argument in the given line.
 * Assumes the part of the line before the specific argument is syntax-valid.
 *
 * @param   *line           The line of assembly code to search for the argument.
 * @param   argumentNum     The number of the argument to search for (starting from 1).
 * @param   isLabel         Indicates whether the line has a label definition.
 *
 * @return  The index of the specified argument in the line, or index of null terminator
 *          of the given line string if not found.
 */
int getArgumentIndex(const char *line, int argumentNum, boolean isLabel);

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

/*
 * Gets the argument data from a given line string.
 *
 * @param   *line           The line string to get the data from.
 * @param   argumentNum     The number of argument to get the data off.
 * @param   isLabel         Flag indicating if the line has a label definition.
 * @param   *argData        Pointer to store the found data.
 * @param   isStrArg        Flag indicating if the argument is a string (special case).
 */
void getArgDataFromLine(const char *line, int argumentNum, boolean isLabel, data_t *argData,
                        boolean isStrArg);

/*
 * Check if the current argument is the last one in the assembly code line.
 *
 * @param   line            The assembly code line to check for the last argument.
 * @param   argumentNum     The current argument number being processed.
 * @param   isLabel         Flag indicating if the line has a label definition.
 *
 * @return  TRUE if the current argument is the last one, FALSE otherwise.
 */
boolean isLastArg(const char *line, int argumentNum, boolean isLabel);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_LINE_DIAGNOSES_H */
