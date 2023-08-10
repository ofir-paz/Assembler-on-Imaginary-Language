/*
 * @author Ofir Paz
 * @version (08/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
#include "../general-enums/indexes.h"
#include "encodingDataStructures/word.h"
/* -------------------------- */

/* ---Macros--- */

/* ---Masking operations--- */

/* Use when 1 <= n <= 8. */
#define get_first_n_bits(byte, n) ((byte) & (FULL_1_BYTE >> (BITS_IN_BYTE - (n))))

#define get_last_n_bits(byte, n) ((byte) & (FULL_1_BYTE << (BITS_IN_BYTE - (n))))

/* Use when low and high are numbers. */
#define isValidWordRange(low, high)\
    ((START_WORD_RANGE <= (low) && (low) <= (high) && (high) <= END_WORD_RANGE)? TRUE : FALSE)

#define range(low, high) ((high) - (low) + 1)

/* Use when 0 <= low <= high <= 7 and val can fit in (high - low + 1) bits. */
#define set_bits_to_val(byte, low, high, val) (byte = \
    ((val) << (low)) | \
    (((low) > ZERO_INDEX)? get_first_n_bits(byte, low) : ZERO_BYTE) | \
    (((high) < BITS_IN_BYTE - 1)? get_last_n_bits(byte, high) : ZERO_BYTE))

/* ------------ */

/* ---Finals--- */
#define FIRST_BIT_ON 1
#define FIRST_PART_OF_WORD 0
#define SECOND_PART_OF_WORD 1
#define SIX_NUMBER 6
#define TWO_NUMBER 2
#define FOUR_NUMBER 4
#define ZERO_BYTE 0
#define FULL_1_BYTE 0xff
#define BITS_IN_BYTE 8
#define START_WORD_RANGE 0
#define END_WORD_RANGE 11
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Checks if the given signed value fits inside a bit array of the given size.
 *
 * @param   size    The size of the bit array.
 * @param   val     The given value to check if it overflows.
 *
 * @return  TRUE if the value overflows, otherwise FALSE.
 */
boolean isOverflow(int size, int val)
{
    int minValInSize = -(FIRST_BIT_ON << (size - 1));
    int maxValInSize = ~(FIRST_BIT_ON << (size - 1));

    return (minValInSize <= val && val <= maxValInSize)? TRUE : FALSE;
}

/*
 * Sets a range of bits in a word to the specified value.
 *
 * @param   word    The word where the bits will be modified.
 * @param   low     The lowest index (0-based) of the bit range to set (including low).
 * @param   high    The highest index (0-based) of the bit range to set (including high).
 * @param   val     The value to which the specified bit range should be set.
 */
void setBitsInRangeToVal(word_t word, int low, int high, int val)
{
    if (isValidWordRange(low, high) == TRUE && isOverflow(range(low, high), val) == FALSE)
    {
        if (high <= BITS_IN_BYTE - 1) /* If the range is just in the first part. */
            set_bits_to_val(word[FIRST_PART_OF_WORD], low, high, val);

        else if (low <= BITS_IN_BYTE - 1) /* If the range is split between the parts. */
        {
            /* Set some of the bits at the end of the first part. */
            set_bits_to_val(word[FIRST_PART_OF_WORD], low, BITS_IN_BYTE - 1,
                            get_first_n_bits(val, BITS_IN_BYTE - low));
            /* Set the rest of the bits at the start of the second part. */
            set_bits_to_val(word[SECOND_PART_OF_WORD], ZERO_INDEX, high - BITS_IN_BYTE,
                            get_last_n_bits(val, high - BITS_IN_BYTE));
        }

        else /* The range is just in the second part. */
            set_bits_to_val(word[SECOND_PART_OF_WORD], low - BITS_IN_BYTE,
                            high - BITS_IN_BYTE, val);
    }
}

/*
 * Convert a word to a Base64 representation.
 *
 * @param   word    The word to be converted.
 */
void convertWordToBase64(word_t word)
{
    /* Conversion is as such: base64Values[i] = i in Base64 */
    char base64Values[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    /* Since a word in the assembly language requires a minimum
     * of two bytes to be represented, We take the first 6 bits of the
     * representation, and the last 6 bits of it and convert them. */
    char firstChar = get_first_n_bits(word[FIRST_PART_OF_WORD], SIX_NUMBER);
    char secondChar = get_last_n_bits(word[FIRST_PART_OF_WORD], TWO_NUMBER) >>
            SIX_NUMBER | get_first_n_bits(word[SECOND_PART_OF_WORD], FOUR_NUMBER) << TWO_NUMBER;

    /* Assign them back to the word in their base 64 equivalents. */
    word[FIRST_PART_OF_WORD] = base64Values[firstChar];
    word[SECOND_PART_OF_WORD] = base64Values[secondChar];
}