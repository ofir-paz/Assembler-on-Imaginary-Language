/*
 * @author Ofir Paz
 * @version (12/08/2023)
 *
 * Header file for the SecondTransitionErrors.c file.
 */

#ifndef MMN_14_SECONDTRANSITIONERRORS_H
#define MMN_14_SECONDTRANSITIONERRORS_H

#include "../error_types/error_types.h"

/* ---------------Prototypes--------------- */

void handleLineErrorInSecondTrans(const char *file_name, int currLine, Error lineError,
                                  boolean *wasError);

Error checkEntryLabelErr(const char *entLabel, NameTable *normalLabels, NameTable *entLabels);

/* ---------------------------------------- */

#endif /* MMN_14_SECONDTRANSITIONERRORS_H */
