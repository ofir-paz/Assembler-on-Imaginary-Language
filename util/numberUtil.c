/*
 * @author Ofir Paz
 * @version (04/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define ZERO_NUMBER 0
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Checks if a given integer is between the specified low and high values (inclusive).
 *
 * @param num     The integer to check.
 * @param low     The lower bound of the range.
 * @param high    The upper bound of the range.
 *
 * @return        TRUE if the given integer is between low and high (inclusive), otherwise FALSE.
 */
boolean between(int num, int low, int high)
{
    return (low <= num && num <= high)? TRUE : FALSE;
}

/*
 * Checks if a given number is negative.
 *
 * @param   num     The number to check if it's negative.
 *
 * @return TRUE if the given number is negative, otherwise FALSE.
 */
boolean isNegative(int num)
{
    return (num < ZERO_NUMBER)? TRUE : FALSE;
}