/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "../encoding/encoding-finals/encoding-finals.h"
#include "../general-enums/indexes.h"
#include "diagnose_line.h"
#include "../general_help_methods.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

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
 * Checks if the give word is a saved word in the language.
 *
 * @param   word The word to check.
 * @return  TRUE if the word is a saved word, otherwise FALSE.
 */
boolean isSavedWord(const char *word)
{
    return (getGuidance(word) == NO_GUIDANCE && getOpcode(word) == NO_OPCODE)? FALSE : TRUE;
}