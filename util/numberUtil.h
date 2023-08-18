/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the numberUtil.c file.
 */

#ifndef MMN_14_NUMBERUTIL_H
#define MMN_14_NUMBERUTIL_H

#include "../new-data-types/boolean.h"

/* ---Macros--- */
#define remove_right_digit(num) ((num) /= 10)
#define get_right_digit(num) ((num) % 10)
/* ------------ */

/* ---------------Prototypes--------------- */

/*
 * Checks if a given integer is between the specified low and high values (inclusive).
 *
 * @param   num     The integer to check.
 * @param   low     The lower bound of the range.
 * @param   high    The upper bound of the range.
 *
 * @return  TRUE if the given integer is between low and high (inclusive), otherwise FALSE.
 */
boolean between(int num, int low, int high);

/*
 * Checks if a given number is negative.
 *
 * @param   num     The number to check if it's negative.
 *
 * @return TRUE if the given number is negative, otherwise FALSE.
 */
boolean isNegative(int num);

/*
 * Counts the amount of digits in a given number.
 *
 * @param   num     The number to count its digits.
 *
 * @return  The number of digits in the given number.
 */
int getDigitCnt(int num);

/* ---------------------------------------- */

#endif /* MMN_14_NUMBERUTIL_H */
