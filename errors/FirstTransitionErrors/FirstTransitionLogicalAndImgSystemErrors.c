/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This file has the functions to check for logical and imaginary system errors
 * in an assembly source line of code.
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../../NameTable/NameTable.h"
#include "../../assembler_ast/assembler_ast.h"
#include "../error_types/error_types.h"
#include "../../general-enums/assemblerFinals.h"
#include "../../diagnoses/assembler_diagnoses.h"
#include "../../util/memoryUtil.h"
/* -------------------------- */

/* ---Finals--- */
/* ------------ */

/* ---Macros--- */
/* ------------ */

/* ---------------Prototypes--------------- */
Error checkOperationArgErrors(ast_t *lineAst);
Error checkGuidanceArgErrors(ast_t *lineAst);
Error checkOneArgOpError(opcodes_t opcode, arg_node_t *destArg);
Error checkTwoArgOpError(opcodes_t opcode, arg_node_t *destArg, arg_node_t *srcArg);
/* ---------------------------------------- */

/*
 * Checks for logical and imaginary system errors in the given built AST.
 *
 * @param   *lineAst    The built AST to check for errors in it.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkErrorsInAstFirstTrans(ast_t *lineAst)
{
    Error errorInAST; /* Error to return. */

    if (getSentence(lineAst).sentenceType == DIRECTION_SENTENCE)
        errorInAST = checkOperationArgErrors(lineAst);

    else /* lineAst.sentenceType == GUIDANCE_SENTENCE */
        errorInAST = checkGuidanceArgErrors(lineAst);

    return errorInAST;
}

/*
 * Checks for a missing argument error in the given AST.
 *
 * @param   *lineAst    The built AST to check for errors in it.
 *
 * @return  The found error, or NO_ERROR if there is none.
 */
Error checkErrorInMissingArg(ast_t *lineAST)
{
    Error missingArgError = NO_ERROR; /* Error to return. */
    opcodes_t opcode = getOpcodeFromAST(lineAST);

    if (getOpGroup(opcode) != ZERO_ARGS) /* If there is a need for an argument. */
        missingArgError = EXPECTED_ARGUMENT_ERR;

    return  missingArgError;
}

/*
 * Checks for errors in the argument of an operation.
 *
 * @param   *lineAst    The AST containing the operation and the arguments.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkOperationArgErrors(ast_t *lineAst)
{
    Error argError = NO_ERROR; /* Error to return. */
    opcodes_t opcode = getOpcodeFromAST(lineAst);
    arg_node_t *firstArg = getArgList(lineAst);
    int argCount = getOpGroup(opcode); /* How many arguments are needed. */

    /* Check for errors specifically by how many arguments the operation needs. */
    if (argCount == ONE_ARGS)
        argError = checkOneArgOpError(opcode, firstArg);

    else if (argCount == TWO_ARGS)
        argError = checkTwoArgOpError(opcode, getNextNode(firstArg), firstArg);

    return argError;
}

/*
 * Checks for errors in the argument of an operation that accepts one argument only.
 *
 * @param   opcode      The opcode of the operation.
 * @param   *destArg    The argument of the operation.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkOneArgOpError(opcodes_t opcode, arg_node_t *destArg)
{
    Error argError = NO_ERROR; /* Error to return. */
    addressing_method_t destMtd = getArgAddressingMethod(destArg);

    /* Check for specific errors. */
    if (validArg(opcode, TRUE, destMtd) == INVALID_ARG_MTD)
        argError = ILLEGAL_DEST_ARG_MTD_ERR;

    else if (isOverflowNumber(destArg, FALSE))
        argError = INSTANT_VALUE_OVERFLOW_ERR;

    return argError;
}

/*
 * Checks for errors in the argument of an operation that accepts two argument only.
 *
 * @param   opcode      The opcode of the operation.
 * @param   *destArg    The destination argument of the operation.
 * @param   *srcArg     The source argument of the operation.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkTwoArgOpError(opcodes_t opcode, arg_node_t *destArg, arg_node_t *srcArg)
{
    Error argError = NO_ERROR; /* Error to return. */
    addressing_method_t destMtd = getArgAddressingMethod(destArg);
    addressing_method_t srcMtd = getArgAddressingMethod(srcArg);

    /* Check for specific errors. */
    if (validArg(opcode, TRUE, destMtd) == INVALID_ARG_MTD)
        argError = ILLEGAL_DEST_ARG_MTD_ERR;

    else if (validArg(opcode, FALSE, srcMtd) == INVALID_ARG_MTD)
        argError = ILLEGAL_SRC_ARG_MTD_ERR;

    else if (isAnyOverflowNumber(srcArg, FALSE))
        argError = INSTANT_VALUE_OVERFLOW_ERR;

    return argError;
}

/*
 * Checks for errors in the guidance of the given AST (assumes the ast has a guidance).
 *
 * @param   *lineAst    The AST containing the operation and the arguments.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
Error checkGuidanceArgErrors(ast_t *lineAst)
{
    Error guidanceArgError = NO_ERROR; /* Error to return. */
    guidance_t guidance = getGuidanceFromAST(lineAst);

    /* Check for specific guidance error. */
    if ((guidance == ent || guidance == ext) &&
        isAllArgsSpecificDataType(getArgList(lineAst), STRING) == FALSE)
            guidanceArgError = ARGUMENT_IS_NOT_LABEL_ERR;

        /* No need to check for .string (was checked in syntax errors). */
    else if (guidance == data && isAllArgsSpecificDataType(getArgList(lineAst), INT) == FALSE)
        guidanceArgError = EXPECTED_NUMBER_ARG_ERR;

    else if (guidance == data && isAnyOverflowNumber(getArgList(lineAst), TRUE))
        guidanceArgError = DATA_VALUE_OVERFLOW_ERR;

    return guidanceArgError;
}

/*
 * Checks for errors in defining a new label.
 *
 * @param   *lineAst        The AST containing the label definition.
 * @param   *normalTable    The normal labels table.
 * @param   *extTable       The external labels table.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
LogicalError checkLabelDefTableError(ast_t *lineAst, NameTable *normalTable, NameTable *extTable)
{
    LogicalError labelDefError = NO_ERROR; /* Error to return. */
    char *labelName = getLabelName(lineAst); /* Save the label name for error diagnoses. */

    /* Check the specific error if there is. */
    if (isNameInTable(normalTable, labelName))
        labelDefError = MULTIPLE_NORMAL_LABEL_DEF_ERR;

    else if (isNameInTable(extTable, labelName))
        labelDefError = LABEL_DEFINED_AS_NORMAL_AND_EXT_ERR;

    (void) clear_ptr(labelName) /* Clear unnecessary variable. */
    return labelDefError;
}

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
                                       NameTable *extLabels)
{
    LogicalError addToEntryTableError = NO_ERROR; /* Error to return. */

    /* Check the specific error if there is. */
    if (isNameInTable(entLabels, label))
        addToEntryTableError = MULTIPLE_ENTRY_LABEL_DEF_ERR;

    else if (isNameInTable(extLabels, label))
        addToEntryTableError = LABEL_DEFINED_AS_ENT_AND_EXT_ERR;

    return addToEntryTableError;
}

/*
 * Checks for errors in adding a new external label to the extern table.
 *
 * @param   *label          The extern label name to check for errors in the addition.
 * @param   *labelsMap[]    Array holding all the different label tables.
 *
 * @return  The specific found error, or NO_ERROR if there is none.
 */
LogicalError checkAddToExternTableError(const char *label, NameTable *labelsMap[])
{
    LogicalError addToEntryTableError = NO_ERROR; /* Error to return. */

    /* Check the specific error if there is. */
    if (isNameInTable(labelsMap[NORMAL], label))
        addToEntryTableError = LABEL_DEFINED_AS_NORMAL_AND_EXT_ERR;

    else if (isNameInTable(labelsMap[ENTRY], label))
        addToEntryTableError = LABEL_DEFINED_AS_ENT_AND_EXT_ERR;

    else if (isNameInTable(labelsMap[EXTERN], label))
        addToEntryTableError = MULTIPLE_EXTERN_LABEL_DEF_ERR;

    return addToEntryTableError;
}

/*
 * Checks if there has been a program memory overflow.
 *
 * @param   *astList    The list of ASTs that summarize the first transition.
 *
 * @return  PROG_MEM_OVERFLOW_ERR on memory overflow error, otherwise NO_ERROR.
 */
ImgSystemError checkFileMemoryOverflow(ast_list_t *astList)
{
    int IC = *getCounterPointer(astList, IC_);
    int DC = *getCounterPointer(astList, DC_);
    int lastWordAddress = IC + DC - PROGRAM_MEM_START;

    return (lastWordAddress >= IMG_SYSTEM_MEMORY_SIZE)? PROG_MEM_OVERFLOW_ERR : NO_ERROR;
}