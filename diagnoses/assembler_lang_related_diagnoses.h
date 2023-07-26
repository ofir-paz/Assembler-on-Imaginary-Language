/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * Header file for the assembler_lang_related_diagnoses.c file.
 */

#ifndef MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H
#define MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H

#include "../new-data-types/boolean.h"

/* ---------------Prototypes--------------- */

/*
 * Checks of the give word is a saved word in the language.
 *
 * @param   word The word to check.
 * @return  TRUE if the word is a saved word, otherwise FALSE.
 */
boolean isSavedWord(const char *word);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_LANG_RELATED_DIAGNOSES_H */
