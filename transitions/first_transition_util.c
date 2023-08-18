/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * This function has the utility methods to assist with the first transition.
 */

/* ---Include header files--- */
#include <string.h>
#include <stddef.h>
#include "../NameTable/NameTable.h"
#include "../assembler_ast/assembler_ast.h"
#include "../general-enums/programFinals.h"
#include "../general-enums/assemblerFinals.h"
#include "../errors/error_types/error_types.h"
#include "../errors/FirstTransitionErrors/FirstTransitionSyntaxErrors.h"
#include "../errors/FirstTransitionErrors/FirstTransitionLogicalAndImgSystemErrors.h"
#include "../diagnoses/assembler_line_diagnoses.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
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

/*
 * Adds data from the processed line to an abstract syntax tree (AST)
 * during the first transition phase.
 *
 * @param   *lineAST  The abstract syntax tree (AST) representing the processed line.
 * @param   *line     The input line of assembly code.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
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

/*
 * Adds a label from the given assembly line to an abstract syntax tree (AST)
 *
 * @param   *lineAST  The abstract syntax tree (AST) representing the processed line.
 * @param   *line     The input line of assembly code.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addLabelFromLineToAST(ast_t *lineAST, const char *line)
{
    Error foundError = NO_ERROR; /* Error to return, assume success. */
    char *label = NULL; /* Will hold the label to add. */

    if (isColonInLineForLabel(line) == TRUE)
        if ((foundError = checkSyntaxErrorInLabel(line)) == NO_ERROR)
            label = getLabelFromLine(line);

    /* Add label (will do nothing if there was an error or there was no label). */
    addLabelToAst(lineAST, label);

    (void) clear_ptr(label) /* Free unnecessary variable (The AST is adding a duplicate) . */
    return foundError;
}

/*
 * Adds a sentence from the given line to an abstract syntax tree (AST)
 * during the first transition phase.
 *
 * @param   *lineAST  The abstract syntax tree (AST) representing the processed line.
 * @param   *line     The input line of assembly code.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
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
    int argumentNum = FIRST_ARGUMENT; /* Will hold the number of argument to add. */
    boolean isLabelDef = isLabel(lineAST);
    opcodes_t opcode = getOpcodeFromAST(lineAST);

    /* Special case for .string guidance. */
    boolean isStrGuidance = (getGuidanceFromAST(lineAST) == str)? TRUE : FALSE;

    if (isLastArg(line, ZERO_NUMBER, isLabel(lineAST)) == FALSE)
        /* Add arguments to AST while an error was not found. */
        while ((foundError = checkSyntaxErrorInArgAndBetween(
                line, argumentNum, isLabelDef, opcode, isStrGuidance)) == NO_ERROR)
        {
            data_t *argData = (data_t *) allocate_space(sizeof(data_t));
            getArgDataFromLine(line, argumentNum, isLabel(lineAST), argData, isStrGuidance);
            addArgumentToAst(lineAST, argData);
            if (isLastArg(line, argumentNum, isLabel(lineAST)) == TRUE) break;
            argumentNum++;
        }
    else /* No arguments, check if it's an error. */
        foundError = checkErrorInMissingArg(lineAST);

    return foundError;
}

/*
 * Adds a label to the specified symbol table during the first transition phase.
 *
 * @param   *label       The label to be added.
 * @param   *labelsMap   An array of symbol tables for label management.
 * @param   table        The type of symbol table to add the label to (NORMAL or EXTERN).
 * @param   *argError    Pointer to an error variable for recording the outcome of the operation.
 */
void addLabelToOtherTable(char *label, NameTable *labelsMap[], label_type_t table,
                          Error *argError)
{
    Error newError; /* Will hold the found error (if there is). */

    if (table == ENTRY)
        newError = addLabelToEntryTable(label, labelsMap[ENTRY], labelsMap[EXTERN]);
    else /* table == EXTERN */
        newError = addLabelToExternTable(label, labelsMap);

    if (*argError == NO_ERROR)
        *argError = newError;
}

/*
 * Adds a label to the entry symbol table during the first transition phase.
 *
 * @param   *label       The label to be added.
 * @param   *entLabels   The entry symbol table for label management.
 * @param   *extLabels   The external symbol table for reference management.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addLabelToEntryTable(char *label, NameTable *entLabels, NameTable *extLabels)
{
    Error argLabelError = checkAddToEntryTableError(label, entLabels, extLabels);

    if (argLabelError == NO_ERROR)
        addLabelToTable(entLabels, my_strdup(label), ZERO_NUMBER);

    return argLabelError;
}

/*
 * Adds a label to the external symbol table during the first transition phase.
 *
 * @param   *label       The label to be added.
 * @param   *labelsMap   An array symbol tables for label management.
 *
 * @return  An error code indicating the outcome of the operation, or NO_ERROR if successful.
 */
Error addLabelToExternTable(char *label, NameTable *labelsMap[])
{
    Error argLabelError = checkAddToExternTableError(label, labelsMap);

    if (argLabelError == NO_ERROR)
        addLabelToTable(labelsMap[EXTERN], my_strdup(label), ZERO_NUMBER);

    return argLabelError;
}

/*
 * Adds a label with an associated address to a symbol table during the first transition phase.
 *
 * @param   *labelMap     The symbol table to which the label is added.
 * @param   *labelName    The name of the label to be added.
 * @param   address       The address associated with the label.
 */
void addLabelToTable(NameTable *labelMap, char *labelName, int address)
{
    (void) addNameToTable(labelMap, labelName);
    (void) setNumberInData(labelMap, labelName, address);
}

/*
 * Updates one of the give counters IC or DC based on the amount of words
 * needs to encode the line of code represented by lineAst.
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

/*
 * Calculates the number of words required to represent an instruction in memory.
 * Assumes that lineAst represents a valid line of code !!
 *
 * @param   *lineAst    The abstract syntax tree (AST) representing the processed line
 *                      with the instruction.
 *
 * @return  The number of words needed to store the instruction.
 */
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

/*
 * Calculates the number of words required to represent data in memory.
 *
 * @param   *lineAst  The abstract syntax tree (AST) representing the processed line.
 *
 * @return  The number of words needed to store the data.
 */
int howManyWordsForData(ast_t *lineAst)
{
    unsigned short amountOfWords = ZERO_WORDS; /* Value to return, reset it to zero. */

    /* Count how many words based on the type of data (numbers or string). */
    if (getSentence(lineAst).sentence.guidance == data) /* Numbers. */
        amountOfWords = getArgAmount(lineAst);

    else if (getSentence(lineAst).sentence.guidance == str) /* String. */
        amountOfWords = strlen(getArgData(getArgList(lineAst)).data.string)
                - TWO_QUOTES + SIZE_FOR_NULL;

    return amountOfWords;
}

/*
 * Updates all the data labels addresses.
 * Basically, separates between the data image and the instruction image.
 *
 * @param   *labels     List of all labels defined in the file.
 * @param   finalIC     The amount of words needed for the instructions in the file.
 */
void updateDataLabels(NameTable *labels, int finalIC)
{
    (void) changeToPosAndAdd(labels, finalIC);
}