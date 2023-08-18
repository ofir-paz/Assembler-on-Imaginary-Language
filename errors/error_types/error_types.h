/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file contains all the error types.
 */

#ifndef MMN_14_ERROR_TYPES_H
#define MMN_14_ERROR_TYPES_H

/* ---Include all error types--- */
#include "error_constant.h"
#include "ImgSystemError.h"
#include "SyntaxError.h"
#include "LogicalError.h"
/* ----------------------------- */

/* Combine all different error types to be represented as int */
typedef int Error;

#endif /* MMN_14_ERROR_TYPES_H */
