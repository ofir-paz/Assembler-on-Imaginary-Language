/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stdlib.h>
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
#define FIRST_ARGUMENT 1
/* ------------ */

/* ---------------Prototypes--------------- */
Error addDataFromLineToAST(ast_t *lineAST, const char *line);
Error addLabelFromLineToAST(ast_t *lineAST, const char *line);
Error addSentenceFromLineToAST(ast_t *lineAST, const char *line);
Error addArgumentsFromLineToAST(ast_t *lineAST, const char *line);
void getArgDataFromLine(const char *line, int argumentNum, boolean isLabel,
                        void **argData, data_type_t *dataType);
void getArgDataFromString(const char *arg, data_type_t dataType, void **argData)
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
        *lineError = checkErrorsInAstFirstTrans(lineAST);

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
        lineError = addSentenceFromLineToAST(lineAST, line);
    if (lineError == NO_ERROR)
        lineError = addArgumentsFromLineToAST(lineAST, line);

    return lineError;
}

Error addLabelFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError = NO_ERROR; /* Error to return, assume success. */
    char *label = NULL;

    if (isColonInLineForLabel(line) == TRUE)
        if ((foundError = checkSyntaxErrorInLabel(line)) == NO_ERROR)
            label = getLabelFromLine(line);

    /* Add label (will do nothing if there was an error or there was no label). */
    addLabelToAst(lineAST, label);

    return foundError;
}

Error addSentenceFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError; /* Error to return. */
    boolean isLabelDef = isLabel(lineAST);

    if ((foundError = checkSyntaxErrorInCommand(line, isLabelDef)) == NO_ERROR)
        addSentenceToAst(lineAST,
                         getCommandFromLine(line, isLabelDef),
                         getSentenceTypeOfLine(line, isLabelDef));

    return foundError;
}

Error addArgumentsFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError = NO_ERROR; /* Error to return, assume success. */
    int argumentNum = FIRST_ARGUMENT;
    boolean isLabelDef = isLabel(lineAST);
    void *argData = NULL;
    data_type_t dataType;

    while ((foundError = checkSyntaxErrorInArgument(line, argumentNum, isLabelDef)) == NO_ERROR &&
           (foundError = checkSyntaxErrorAfterArgument(line, argumentNum, isLabelDef)) == NO_ERROR)
    {
        getArgDataFromLine(line, argumentNum, isLabel(lineAST), &argData, &dataType);
        addArgumentToAst(lineAST, argData, dataType);
        if (isLastArg(line, argumentNum, isLabel(lineAST)) == TRUE) break;
        argumentNum++;
    }

    return foundError;
}

void getArgDataFromLine(const char *line, int argumentNum, boolean isLabel,
                        void **argData, data_type_t *dataType)
{
    char *arg;
    findArg(line, &arg, argumentNum, isLabel);
    getArgDataTypeFromString(arg, dataType);
    getArgDataFromString(arg, *dataType, argData);
    (void) free_ptr(POINTER(arg));
}

void getArgDataFromString(const char *arg, data_type_t dataType, void **argData)
{
    switch (dataType)
    {
        case INT:
            **((int **) argData) = atoi(arg);
            break;
        case STRING:
            *((char **) argData) = arg;
            break;
        case REG:
            **((register_t **) argData) = getRegister(arg);
            break;
    }
}

void addLabelToTable(NameTable *labelMap, char *labelName, int address)
{
    (void) addNameToTable(labelMap, labelName);
    (void) setNumberInData(labelMap, labelName, address);
}