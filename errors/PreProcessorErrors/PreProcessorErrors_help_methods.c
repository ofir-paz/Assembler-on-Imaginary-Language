/*
 * @author Ofir Paz
 * @version (26/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../../new-data-types/boolean.h"
#include "../../diagnoses/diagnose_line.h"
#include "../../general_help_methods.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Checks if the first word in the given line is a macro saved word in the language.
 * The saved words are: "mcro" and "endmcro".
 *
 * @param   *line The given line string to check the first word in it.
 * @return  TRUE if the first word is a macro saved word, otherwise FALSE.
 */
boolean isFirstWordMcroDef(const char *line)
{
    boolean isFirstWordMcroDef = FALSE; /* Value to return. */
    char *firstWord; /* Will hold the first word. */
    findWord(line, &firstWord, FIRST_WORD); /* Find the first word in line. */

    /* Assign value to return to TRUE if the first word is mcro saved word */
    if (sameStrings(firstWord, "mcro") || sameStrings(firstWord, "endmcro"))
        isFirstWordMcroDef = TRUE;

    free_ptr(POINTER(firstWord)); /* Free unnecessary variable. */
    return isFirstWordMcroDef;
}