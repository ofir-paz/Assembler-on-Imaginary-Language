/*
 * @author Ofir Paz
 * @version (29/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <string.h>
#include <stddef.h>
#include "../NameTable/NameTable.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/assemblerFinals.h"
#include "../errors/FirstTransitionErrors/FirstTransitionSyntaxErrors.h"
#include "../diagnoses/assembler_line_diagnoses.h"
#include "../util/memoryUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */

/* Word counter */
enum {ZERO_WORDS, ONE_WORDS, TWO_WORDS, THREE_WORDS};

#define FIRST_ARGUMENT 1
/* ------------ */

/* ---------------Prototypes--------------- */
Error addDataFromLineToAST(ast_t *lineAST, const char *line);
Error addLabelFromLineToAST(ast_t *lineAST, const char *line);
Error addSentenceFromLineToAST(ast_t *lineAST, const char *line);
Error addArgumentsFromLineToAST(ast_t *lineAST, const char *line);
Error addLabelToEntryTable(char *label, NameTable *entLabels, NameTable *extLabels);
Error addLabelToExternTable(char *label, NameTable *labelsMap[]);
void addLabelToTable(NameTable *labelMap, char *labelName, int address);
int howManyWordsForInstruction(ast_t *lineAst);
int howManyWordsForData(ast_t *lineAst);
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

    (void) clear_ptr(label) /* Free unnecessary variable. */
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
    opcodes_t opcode = getOpcodeFromAST(lineAST);
    boolean isStrGuidance = (getGuidanceFromAST(lineAST) == str)? TRUE : FALSE;

    if (isLastArg(line, ZERO_NUMBER, isLabel(lineAST)) == FALSE)
        while ((foundError = checkSyntaxErrorInArgAndBetween(
                line, argumentNum, isLabelDef, opcode, isStrGuidance)) == NO_ERROR)
        {
            data_t *argData = (data_t *) allocate_space(sizeof(data_t));
            getArgDataFromLine(line, argumentNum, isLabel(lineAST), argData);
            addArgumentToAst(lineAST, argData);
            if (isLastArg(line, argumentNum, isLabel(lineAST)) == TRUE) break;
            argumentNum++;
        }

    return foundError;
}

void addLabelToOtherTable(char *label, NameTable *labelsMap[], label_type_t table,
                          Error *argError)
{
    if (table == ENTRY)
        *argError = addLabelToEntryTable(label, labelsMap[ENTRY],
                                         labelsMap[EXTERN]);
    else /* table == EXTERN */
        *argError = addLabelToExternTable(label, labelsMap);
}

Error addLabelToEntryTable(char *label, NameTable *entLabels, NameTable *extLabels)
{
    Error argLabelError = getLogicalErrorInAddToEntryTable(label, entLabels, extLabels);

    if (argLabelError == NO_ERROR)
        addLabelToTable(entLabels, label, ZERO_NUMBER);

    return argLabelError;
}

Error addLabelToExternTable(char *label, NameTable *labelsMap[])
{
    Error argLabelError = getLogicalErrorInAddToExternTable(label, labelsMap);

    if (argLabelError == NO_ERROR)
        addLabelToTable(labelsMap[EXTERN], label, ZERO_NUMBER);

    return argLabelError;
}

void addLabelToTable(NameTable *labelMap, char *labelName, int address)
{
    (void) addNameToTable(labelMap, labelName);
    (void) setNumberInData(labelMap, labelName, address);
}

/*
 * Updates one of the give counters IC or DC based on the amount of words
 * needs to encode the line of code represented by lienAst.
 *
 * Assumes that lineAst represents a valid line of code !!
 *
 * @param   *lineAst    The AST representing the line of code.
 * @param   *IC         Instruction counter.
 * @param   *DC         Data counter.
 */
void updateCounters(ast_t *lineAst, int *IC, int *DC)
{
    if (getSentence(lineAst).sentenceType == DIRECTION_SENTENCE)
        *IC += howManyWordsForInstruction(lineAst);
    else /* lineAst.sentenceType == GUIDANCE_SENTENCE */
        *DC += howManyWordsForData(lineAst);
}

int howManyWordsForInstruction(ast_t *lineAst)
{
    int amountOfWords = ZERO_WORDS; /* Value to return, reset it to zero. */
    arg_node_t *firstArg = getArgList(lineAst); /* Helper variable. */

    if (firstArg == NULL)
        amountOfWords = ONE_WORDS; /* Only command. */

    /* One argument only OR two register arguments. */
    else if (getNextNode(firstArg) == NULL ||
            (getArgAddressingMethod(firstArg) == DIRECT_REGISTER &&
             getArgAddressingMethod(getNextNode(firstArg)) == DIRECT_REGISTER))
        amountOfWords = TWO_WORDS;

    else /* Two arguments, not both of them are registers. */
        amountOfWords = THREE_WORDS;

    return amountOfWords;
}

int howManyWordsForData(ast_t *lineAst)
{
    unsigned short amountOfWords = ZERO_WORDS; /* Value to return, reset it to zero. */

    if (getSentence(lineAst).sentence.guidance == data)
        amountOfWords = getArgAmount(lineAst);

    else if (getSentence(lineAst).sentence.guidance == str)
        amountOfWords = strlen(getArgData(getArgList(lineAst)).data.string)
                - TWO_QUOTES + SIZE_FOR_NULL;

    return amountOfWords;
}

void updateDataLabels(NameTable *labels, int finalIC)
{
    (void) changeToPosAndAdd(labels, finalIC);
}