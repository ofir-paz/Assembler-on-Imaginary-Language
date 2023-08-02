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
ast_t *buildAstFromLine(const char *line, Error *lineError) {
    ast_t *lineAst = creatAst(); /* Create the AST. */
    char *label = NULL; /* Will hold the label name to insert to the ast (if there is a label). */
    int statement; /* Will hold the statement to insert to the ast. */
    sentence_type_t sentenceType; /* Will hold the type of sentence (line). */
    data_t *dataArr;

    *lineError = collectDataFromLine(line, &label, &statement, &sentenceType, &dataArr);

    if (*lineError == NO_ERROR)
    {
        addLabelToAst(lineAst, label);
        addSentenceToAst(lineAst, sentenceType, statement);
        *lineError = checkFirstTransLogicalErrorsInLine(lineAst);
    }

    (void) free_ptr(POINTER(label)); /* Free unnecessary variable. */
    return lineAst;
}

Error collectDataFromLine(const char *line, char **label, int *statement,
                          sentence_type_t *sentenceType, data_t **dataArr)
{
    Error lineError; /* Value to return, will represent the error found in the line. */

    /* Get the tokens of the line or errors found in the process. */
    lineError = getLabel(line, label);
    if (lineError == NO_ERROR) /* Continue to next token if there was no error... */
        lineError = getStatement(line, statement, sentenceType, *label);
    if (lineError == NO_ERROR)
        lineError = getArguments(line, dataArr, *label);

    return lineError;
}