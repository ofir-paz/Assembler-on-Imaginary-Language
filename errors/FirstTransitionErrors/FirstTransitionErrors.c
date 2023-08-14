/*
 * @author Ofir Paz
 * @version (07/08/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include "../error_types/error_types.h"
#include "../../NameTable/NameTable.h"
#include "../../assembler_ast/assembler_ast.h"
#include "../../general-enums/indexes.h"
#include "../../general-enums/neededKeys.h"
#include "../errors.h"
#include "FirstTransitionSpecificErrorCheck.h"
#include "../../diagnoses/assembler_lang_related_diagnoses.h"
#include "../../diagnoses/diagnose_util.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
SyntaxError checkSyntaxErrorInGuidance(const char *guidanceLine);
SyntaxError checkSyntaxErrorInOperation(const char *operationLine);
/* ---------------------------------------- */

void handle_FirstTransLine_Error(const char *file_name, int lineNumber, Error lineError)
{
    print_assembler_ERR(lineError, file_name, lineNumber);
}

Error checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable)
{
    return NO_ERROR;
}

Error checkErrorsInAstFirstTrans(ast_t *lineAst)
{
    return NO_ERROR;
}

/*
 * Checks for syntax errors in label definition.
 * Assuming there is a colon in the line, and his position is not beyond the start
 * of the second word.
 *
 * @param   *line   The line to check for errors in.
 *
 * @return  The label definition syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInLabel(const char *line)
{
    SyntaxError labelDefError = NO_ERROR;
    const char *labelLine = line + nextCharIndex(line, MINUS_ONE_INDEX);

    /* Checking every possible syntax error in the label definition. */
    if (isMissingLabel(labelLine))
        labelDefError = EXPECTED_LABEL_ERR;
    else if (isEmptyBetweenLabelAndColon(labelLine))
        labelDefError = EMPTY_BETWEEN_LABEL_AND_COLON_ERR;
    else if (isLabelStartWithNumber(labelLine))
        labelDefError = LABEL_START_WITH_NUM_ERR;
    else if (isLabelStartWithIllegalChar(labelLine))
        labelDefError = LABEL_START_WITH_ILLEGAL_CHAR_ERR;
    else if (isLabelContainsIllegalChar(labelLine))
        labelDefError = LABEL_CONTAINS_ILLEGAL_CHAR_ERR;
    else if (isLabelTooLong(labelLine))
        labelDefError = LABEL_TOO_LONG_ERR;
    else if (isLabelSavedWord(labelLine))
        labelDefError = LABEL_IS_SAVED_WORD_ERR;

    return labelDefError;
}

/*
 * Checks for syntax errors in the command of the given line.
 *
 * @param   line        The input line to check for syntax errors in its command.
 * @param   isLabelDef  Flag indicating if the line has a label definition.
 *
 * @return  The command syntax error found in the line, or NO_ERROR if there isn't.
 */
SyntaxError checkSyntaxErrorInCommand(const char *line, boolean isLabelDef)
{
    SyntaxError commandError = NO_ERROR; /* Value to return, assume no error. */
    const char *commandLine = line + getCommandStartIndex(line, isLabelDef);

    /* Check which type of command to diagnose to error of. */
    if (isCurrCharDot(commandLine, ZERO_INDEX))
        commandError = checkSyntaxErrorInGuidance(commandLine);
    else
        commandError = checkSyntaxErrorInOperation(commandLine);

    return commandError;
}

SyntaxError checkSyntaxErrorInGuidance(const char *guidanceLine)
{

}

SyntaxError checkSyntaxErrorInOperation(const char *operationLine)
{

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
