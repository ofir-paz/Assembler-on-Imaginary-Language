/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../NameTable/NameTable.h"
#include "../encoding/assembler_ast.h"
#include "../errors/error_types/error_types.h"
#include "../diagnoses/assembler_lang_related_diagnoses.h"
#include "../diagnoses/diagnose_line.h"
#include "../util/memoryUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
/* ------------ */

/* ---------------Prototypes--------------- */
Error collectDataFromLine(const char *line, char **label, int *statement,
                          sentence_type_t *sentenceType, data_t **dataArr);
/* ---------------------------------------- */

/*
 * Build an abstract syntax tree (AST) from the given line of assembly code.
 *
 * @param   line        The line of assembly code to build the AST from.
 * @param   lineError   Pointer to an Error variable that will be set if there are errors
 *                      in the line.
 *
 * @return  Pointer to the root of the AST, or NULL if there was an error during the build process.
 */
ast_t *buildAstFromLine(const char *line, Error *lineError)
{
    ast_t *lineAST = creatAst(); /* Create the AST. */
    *lineError = addDataFromLineToAST(lineAST, line);

    if (*lineError == NO_ERROR) /* Check logical errors in the code if it passed syntax check. */
        *lineError = checkFirstTransLogicalErrorsInLine(lineAst);

    if (*lineError != NO_ERROR)
        deleteAst(&lineAST);

    return lineAST;
}

Error addDataFromLineToAST(ast_t *lineAST, const char *line)
{
    Error lineError; /* Value to return, will represent the error found in the line. */

    /* Get the tokens of the line or errors found in the process. */
    lineError = addLabelFromLineToAST(lineAST, line);
    if (lineError == NO_ERROR) /* Continue to next token if there was no error... */
        lineError = addStatementFromLineToAST(lineAST, line);
    if (lineError == NO_ERROR)
        lineError = addArguemntsFromLineToAST(lineAST, line);

    return lineError;
}

Error addLabelFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError = NO_ERROR; /* Error to return, assume success. */
    char *label = NULL;

    if (isColonInLineForLabel(line) == TRUE)
        if ((foundError = checkSyntaxErrorInLabel(line)) == NO_ERROR)
            findWord(line, &label, FIRST_WORD);

    /* Add label (will do nothing if there was an error). */
    addLabelToAst(lineAST, label);

    return foundError;
}

Error addSentenceFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError = NO_ERROR; /* Error to return, assume success. */
    word_number sentenceNumber = (isLabel(lineAST) == TRUE)? SECOND_WORD : FIRST_WORD;

    if (isSavedWordInLine(line, sentenceNumber))
        addSentenceToAst(lineAST,
                         getCommandFromLine(line, sentenceNumber),
                         getSentenceTypeOfLine(line, sentenceNumber));

    else
        foundError = checkSyntaxErrorInCommand(line, sentenceNumber);

    return foundError;
}