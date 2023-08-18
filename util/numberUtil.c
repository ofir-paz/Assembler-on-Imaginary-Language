/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the function to assist with number related issues.
 */

/* ---Include header files--- */
#include "../new-data-types/boolean.h"
/* -------------------------- */

/* ---Finals--- */
#define ONE_DIGIT 1
#define ZERO_NUMBER 0
/* ------------ */

/* ---Macros--- */
#define remove_right_digit(num) ((num) /= 10)
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

/*
 * Checks if a given integer is between the specified low and high values (inclusive).
 *
 * @param   num     The integer to check.
 * @param   low     The lower bound of the range.
 * @param   high    The upper bound of the range.
 *
 * @return  TRUE if the given integer is between low and high (inclusive), otherwise FALSE.
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

/*
 * Counts the amount of digits in a given number.
 *
 * @param   num     The number to count its digits.
 *
 * @return  The number of digits in the given number.
 */
int getDigitCnt(int num)
{
    int cnt; /* Counter to return. */

    /* Add one to the counter for every digit. */
    for (cnt = ONE_DIGIT; remove_right_digit(num); cnt++);

    return cnt;
}