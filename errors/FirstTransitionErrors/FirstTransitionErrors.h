/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * Header file for the FirstTransitionErrors.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONERRORS_H
#define MMN_14_FIRSTTRANSITIONERRORS_H

#include "../error_types/error_types.h"

/* ---------------Prototypes--------------- */

void handle_FirstTransLine_Error(const char *file_name, int lineNumber, Error lineError);

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable);

Error checkErrorsInAstFirstTrans(ast_t *lineAst);

SyntaxError checkSyntaxErrorInLabel(const char *line);

SyntaxError checkSyntaxErrorInCommand(const char *line, boolean isLabelDef);

Error checkSyntaxErrorInArgAndBetween(const char *line, int argumentNum, boolean isLabelDef);

Error getLogicalErrorInAddToEntryTable(const char *label, NameTable *entLabels,
                                       NameTable *extLabels);

Error getLogicalErrorInAddToExternTable(const char *label, NameTable *labelsMap[]);

/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONERRORS_H */
