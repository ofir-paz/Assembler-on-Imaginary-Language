/*
 * @author Ofir Paz
 * @version (28/07/2023)
 *
 * This file ...
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../new-data-types/boolean.h"
#include "encoding-finals/encoding_finals.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define SUCCESS_CODE 0
#define INVALID_GIVEN_PARAM_CODE (-1)
#define UNKNOWN_NUMBER 0
#define FIRST_ARG 1
/* ------------ */

/* ---------------Abstract syntax tree--------------- */

typedef enum {INT, STRING, REG} data_type_t;

/* This is an argument data type. represents an argument and it's data. */
typedef struct
{
    union
    {
        short int num;
        char *string; /* Can be a label name or string */
        register_t reg;
    } data;
    data_type_t dataType; /* Will hold the type of data of the argument. */
} data_t; /* Will be the data of the argument (data; label name; register) */

/* This is an argument node type. will represent parameters of sentences. */
typedef struct arg_node_t
{
    unsigned short int paramNum; /* Current number of argument in sentence */
    data_t argData;
    addressing_method_t addressingMethod;
    struct arg_node_t *nextArg; /* Next argument. will be NULL if there are no more arguments. */
} arg_node_t; /* Argument node type */

/* This is a sentence node type. will represent the sentence. */
typedef struct
{
    statement_t statement; /* Will be the statement, opcode or guidance. */
    struct arg_node_t *argListHead; /* List of arguments for the sentence. */
} sentence_node_t; /* Sentence node type. */

/* This is the abstract syntax tree. It is a data structure representing a line of code
 * in the imaginary assembly language. */
typedef struct
{
    boolean isLabel;
    sentence_node_t *sentenceNode;
} ast_t; /* ast (abstract syntax tree) type. */

/* This is a data structure with a purpose to save a list of asts. */
typedef struct ast_list_node_t
{
    ast_t *ast;
    struct ast_node_list_t *next;
} ast_list_node_t; /* ast list type. */

typedef struct
{
    ast_list_node_t *head;
    ast_list_node_t *tail;
} ast_list_t;

/* -------------------------------------------------- */

/* ---------------Prototypes--------------- */
/* ---------------------------------------- */

ast_list_t *createAstList()
{
    /* Creating the list. */
    ast_list_t *newAstList = (ast_list_t *) allocate_space(sizeof(ast_list_t));
    newAstList -> head = NULL; /* Resetting it. */
    newAstList -> tail = NULL; /* Resetting it. */
    return newAstList;
}

ast_list_node_t *createAstListNode(ast_t **ast)
{
    /* Creating the list node. */
    ast_list_node_t *newAstListNode =
            (ast_list_node_t *) allocate_space(sizeof(ast_list_node_t));
    newAstListNode -> ast = *ast; /* Adding the given ast to the node. */
    newAstListNode -> next = NULL; /* Resetting the 'next' attribute. */
    return newAstListNode;
}

ast_t *creatAst(boolean isLabel)
{
    ast_t *newAst = (ast_t *) allocate_space(sizeof(ast_t)); /* Creating the ast. */
    newAst -> isLabel = isLabel; /* Setting the 'isLabel' attribute to the given boolean. */
    newAst -> sentenceNode = NULL; /* Resetting the 'sentenceNode' attribute. */
    return newAst;
}

int addAstToList(ast_list_t *astList, ast_t **ast)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Status code to return. */

    if (astList != NULL)
    {
        ast_list_node_t *newAstListNode = createAstListNode(ast);
        if (astList -> head == NULL)
            astList -> head = astList -> tail = newAstListNode;

        else{
            astList -> tail -> next = newAstListNode;
            astList -> tail = newAstListNode;
        }
        returnCode = SUCCESS_CODE;
    }

    return returnCode;
}

sentence_node_t *createSentenceNode(statement_t statement)
{
    sentence_node_t *newSentenceNode =
            (sentence_node_t *) allocate_space(sizeof(sentence_node_t));
    newSentenceNode -> statement = statement;
    newSentenceNode -> argListHead = NULL;
    return newSentenceNode;
}

statement_t createStatement(sentence_type_t sentenceType, int statement)
{
    statement_t newStatement;
    newStatement.sentenceType = sentenceType;
    if (sentenceType == DIRECTION_SENTENCE)
        newStatement.statement.opcode = statement;
    else
        newStatement.statement.guidance = statement;

    return newStatement;
}

void addSentenceToAst(ast_t *ast, sentence_type_t sentenceType, int statement)
{
    statement_t statementOfNewSentence = createStatement(sentenceType, statement);
    sentence_node_t *newSentenceNode = createSentenceNode(statementOfNewSentence);
    ast -> sentenceNode = newSentenceNode;
}

data_t createData(void *data, data_type_t dataType)
{
    data_t newData;
    newData.dataType = dataType;

    switch (dataType)
    {
        case INT:
            newData.data.num = *((short int *) data);
            break;
        case STRING:
            newData.data.string = my_strdup((char *)data);
            break;
        case REG:
            newData.data.reg = *((register_t *) data);
            break;
    }

    return newData;
}

addressing_method_t findAddressingMethod(ast_t *ast, data_type_t dataType)
{
    addressing_method_t addressingMethod = NO_ADD_METHOD;
    if (ast -> sentenceNode -> statement.sentenceType == DIRECTION_SENTENCE)
    {
        switch (dataType) {
            case INT:
                addressingMethod = INSTANT;
                break;
            case STRING:
                addressingMethod = DIRECT;
                break;
            case REG:
                addressingMethod = DIRECT_REGISTER;
                break;
        }
    }
    return addressingMethod;
}

arg_node_t *createArgumentNode(void *data, data_type_t dataType)
{
    arg_node_t *newArgNode = (arg_node_t *) allocate_space(sizeof(arg_node_t));
    newArgNode -> paramNum = UNKNOWN_NUMBER;
    newArgNode -> argData = createData(data, dataType);
    newArgNode -> addressingMethod = NO_ADD_METHOD;
    newArgNode -> nextArg = NULL;
    return newArgNode;
}

arg_node_t *gotoLastArgNode(ast_t *ast)
{
    arg_node_t *lastNode = NULL;

    if (ast != NULL)
        /* Take lastNode to the last node of the argument list in the ast.
         * If the head is NULL, lastNode will also be NULL. */
        for (lastNode = ast -> sentenceNode -> argListHead;
            lastNode != NULL && lastNode -> nextArg != NULL; lastNode = lastNode -> nextArg);
    return lastNode;
}

void addArgumentToAst(ast_t *ast, void *data, data_type_t dataType)
{
    arg_node_t *newArgNode = createArgumentNode(data, dataType);
    arg_node_t *lastNode = gotoLastArgNode(ast);
    if (lastNode == NULL)
    {
        newArgNode -> paramNum = 1;
    }
}

int deleteAst(ast_t **pAst);
int deleteAstList(ast_list_t **pAstList);