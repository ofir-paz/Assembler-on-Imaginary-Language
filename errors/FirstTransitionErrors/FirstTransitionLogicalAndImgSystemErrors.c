/*
 * @author Ofir Paz
 * @version (16/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../../NameTable/NameTable.h"
#include "../../assembler_ast/assembler_ast.h"
#include "../error_types/error_types.h"
/* -------------------------- */

/* ---Finals--- */
/* ------------ */

/* ---Macros--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable)
{
    return NO_ERROR;
}

Error checkErrorsInAstFirstTrans(ast_t *lineAst)
{
    return NO_ERROR;
}

Error getLogicalErrorInAddToEntryTable(const char *label, NameTable *entLabels,
                                       NameTable *extLabels)
{
    return NO_ERROR;
}

Error getLogicalErrorInAddToExternTable(const char *label, NameTable *labelsMap[])
{
    return NO_ERROR;
}