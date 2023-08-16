/*
 * @author Ofir Paz
 * @version (16/08/2023)
 *
 * Header file for the FirstTransitionLogicalAndImgSystemErrors.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H
#define MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H

/* ---------------Prototypes--------------- */

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable);

Error checkErrorsInAstFirstTrans(ast_t *lineAst);

Error getLogicalErrorInAddToEntryTable(const char *label, NameTable *entLabels,
                                       NameTable *extLabels);

Error getLogicalErrorInAddToExternTable(const char *label, NameTable *labelsMap[]);

/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H */
