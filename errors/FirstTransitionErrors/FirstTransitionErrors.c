/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../error_types/error_types.h"
#include "../../NameTable/NameTable.h"
#include "../../encoding/assembler_ast.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

Error handle_FirstTransLine_Error(const char *file_name, int lineNumber, ast_t *lineAst,
                                  Error lineError)
{
    return NO_ERROR;
}

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable)
{
    return NO_ERROR;
}

Error checkErrorsInAstFirstTrans(ast_t *lineAst)
{
    return NO_ERROR;
}

Error checkSyntaxErrorInLabel(const char *line)
{
    return NO_ERROR;
}

Error checkSyntaxErrorInCommand(const char *line, boolean isLabelDef)
{
    return NO_ERROR;
}

void handleExceptionsAndWarningInFirstArg(ast_t *lineAST, const char *line, Error *foundError)
{

}

Error checkSyntaxErrorInArgAndBetween(const char *line, int argumentNum, boolean isLabelDef)
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
