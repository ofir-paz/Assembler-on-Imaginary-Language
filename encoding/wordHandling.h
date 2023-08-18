/*
 * @author Ofir Paz
 * @version (08/08/2023)
 *
 * Header file for the encodingUtil.c file.
 */

#ifndef MMN_14_WORDHANDLING_H
#define MMN_14_WORDHANDLING_H

/* ---------------Prototypes--------------- */

#include "encodingDataStructures/word.h"

/* ---Typedef prototype for encapsulation--- */
/* ----------------------------------------- */

/*
 * Checks if the given signed value fits inside a bit array of the given size.
 *
 * @param   size    The size of the bit array.
 * @param   val     The given signed value to check if it overflows.
 *
 * @return  TRUE if the value overflows, otherwise FALSE.
 */
boolean isSignedOverflow(int size, long int val);

/*
 * Sets a range of bits in a word to the specified value.
 *
 * @param   word    The word where the bits will be modified.
 * @param   low     The lowest index (0-based) of the bit range to set (including low).
 * @param   high    The highest index (0-based) of the bit range to set (including high).
 * @param   val     The value to which the specified bit range should be set.
 */
void setBitsInRangeToVal(word_t word, int low, int high, int val);

/*
 * Convert a word to a Base64 representation.
 *
 * @param   word    The word to be converted.
 * @param   word64  The word to hold the Base64 converted word.
 */
void convertWordToBase64(const word_t word, word_t word64);

/* ---------------------------------------- */

#endif /* MMN_14_WORDHANDLING_H */
