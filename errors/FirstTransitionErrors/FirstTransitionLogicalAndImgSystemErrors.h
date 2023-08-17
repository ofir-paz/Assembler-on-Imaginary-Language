/*
 * @author Ofir Paz
 * @version (16/08/2023)
 *
 * Header file for the FirstTransitionLogicalAndImgSystemErrors.c file.
 */

#ifndef MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H
#define MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H

/* ---------------Prototypes--------------- */

/*
 * Checks for logical and imaginary system errors in the given built AST.
 *
 * @param   *lineAst    The built AST to check for errors in it.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkErrorsInAstFirstTrans(ast_t *lineAst);

/*
 * Checks for a missing argument error in the given AST.
 *
 * @param   *lineAst    The built AST to check for errors in it.
 *
 * @return  The found error, or NO_ERROR if there is none.
 */
Error checkErrorInMissingArg(ast_t *lineAST);

/*
 * Checks for errors in defining a new label.
 *
 * @param   *lineAst        The AST containing the label definition.
 * @param   *normalTable    The normal labels table.
 * @param   *extTable       The external labels table.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
LogicalError checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable);

/*
 * Checks for errors in adding a new entry label to the entry table.
 *
 * @param   *label          The entry label name to check for errors in the addition.
 * @param   *entLabels      The entry labels table.
 * @param   *extTable       The external labels table.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
LogicalError checkAddToEntryTableError(const char *label, NameTable *entLabels,
                                       NameTable *extLabels);

/*
 * Checks for errors in adding a new external label to the extern table.
 *
 * @param   *label          The extern label name to check for errors in the addition.
 * @param   *labelsMap[]    Array holding all the different label tables.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
LogicalError checkAddToExternTableError(const char *label, NameTable *labelsMap[]);

/*
 * Checks if there has been a program memory overflow.
 *
 * @param   *astList    The list of ASTs that summarize the first transition.
 *
 * @return  PROG_MEM_OVERFLOW_ERR on memory overflow error, otherwise NO_ERROR.
 */
ImgSystemError checkFileMemoryOverflow(ast_list_t *astList);

/* ---------------------------------------- */

#endif /* MMN_14_FIRSTTRANSITIONLOGICALANDIMGSYSTEMERRORS_H */
