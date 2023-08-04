/*
 * @author Ofir Paz
 * @version (04/08/2023)
 *
 * Header file for the numberUtil.c file.
 */

#ifndef MMN_14_NUMBERUTIL_H
#define MMN_14_NUMBERUTIL_H

#include "../new-data-types/boolean.h"

/* ---------------Prototypes--------------- */

/*
 * Checks if a given integer is between the specified low and high values (inclusive).
 *
 * @param num     The integer to check.
 * @param low     The lower bound of the range.
 * @param high    The upper bound of the range.
 *
 * @return        TRUE if the given integer is between low and high (inclusive), otherwise FALSE.
 */
boolean between(int num, int low, int high);

/* ---------------------------------------- */

#endif /* MMN_14_NUMBERUTIL_H */
