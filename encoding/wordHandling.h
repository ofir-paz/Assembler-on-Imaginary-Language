/*
 * @author Ofir Paz
 * @version (08/08/2023)
 *
 * Header file for the encodingUtil.c file.
 */

#ifndef MMN_14_WORDHANDLING_H
#define MMN_14_WORDHANDLING_H

/* ---------------Prototypes--------------- */

/*
 * Checks if the given signed value fits inside a bit array of the given size.
 *
 * @param   size    The size of the bit array.
 * @param   val     The given value to check if it overflows.
 *
 * @return  TRUE if the value overflows, otherwise FALSE.
 */
boolean isOverflow(int size, int val);

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
 */
void convertWordToBase64(word_t word);

/* ---------------------------------------- */

#endif /* MMN_14_WORDHANDLING_H */