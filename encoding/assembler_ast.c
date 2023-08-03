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
    sentence_t sentence; /* Will be the sentence, opcode or guidance. */
    arg_node_t *argListHead; /* List of arguments for the sentence. */
} sentence_node_t; /* Sentence node type. */

/* This is the abstract syntax tree. It is a data structure representing a line of code
 * in the imaginary assembly language. */
typedef struct
{
    char *label;
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
data_t createData(void *data, data_type_t dataType);
addressing_method_t findAddressingMethod(ast_t *ast, data_type_t dataType);
arg_node_t *gotoLastArgNode(ast_t *ast);
/* ---------------------------------------- */

/*
 * Creates an empty AST (Abstract Syntax Tree) list.
 *
 * @return  ast_list_t* A pointer to the newly created ast list.
 */
ast_list_t *createAstList(void )
{
    /* Creating the list. */
    ast_list_t *newAstList = (ast_list_t *) allocate_space(sizeof(ast_list_t));
    newAstList -> head = NULL; /* Resetting it. */
    newAstList -> tail = NULL; /* Resetting it. */
    return newAstList;
}

/*
 * Creates a new AST list node with the given AST pointer.
 *
 * @param   **ast Pointer to the AST (Abstract Syntax Tree) to be stored in the new node.
 *
 * @return  ast_list_node_t* A pointer to the newly created AST list node.
 */
ast_list_node_t *createAstListNode(ast_t **ast)
{
    /* Creating the list node. */
    ast_list_node_t *newAstListNode =
            (ast_list_node_t *) allocate_space(sizeof(ast_list_node_t));
    newAstListNode -> ast = *ast; /* Adding the given ast to the node. */
    newAstListNode -> next = NULL; /* Resetting the 'next' attribute. */
    return newAstListNode;
}

/*
 * Creates a new AST (Abstract Syntax Tree) to represent a line of assembly code.
 *
 * @return  A pointer to the newly created AST.
 */
ast_t *creatAst(void )
{
    ast_t *newAst = (ast_t *) allocate_space(sizeof(ast_t)); /* Creating the ast. */
    newAst -> label = NULL; /* Resetting the label attribute to NULL. */
    newAst -> sentenceNode = NULL; /* Resetting the 'sentenceNode' attribute. */
    return newAst;
}

/*
 * Creates a sentence node to hold a sentence.
 * A sentence is an opcode or a guidance defined in the assembly language.
 *
 * @param   sentence The sentence to be held by the sentence node.
 *
 * @return  Pointer to the newly created sentence node.
 */
sentence_node_t *createSentenceNode(sentence_t sentence)
{
    /* Create the new sentence node. */
    sentence_node_t *newSentenceNode =
            (sentence_node_t *) allocate_space(sizeof(sentence_node_t));

    /* Initialize its attributes. */
    newSentenceNode -> sentence = sentence;
    newSentenceNode -> argListHead = NULL;

    return newSentenceNode;
}

/*
 * Creates a sentence of a given sentence type and value.
 * A sentence is an opcode or a guidance defined in the assembly language.
 *
 * @param   sentence The value of the sentence.
 * @param   sentenceType The type of sentence.
 *
 * @return  The created sentence.
 */
sentence_t createSentence(int sentence, sentence_type_t sentenceType)
{
    sentence_t newSentence; /* sentence to return. */
    newSentence.sentenceType = sentenceType;

    /* Add sentence value to sentence accordingly. */
    if (sentenceType == DIRECTION_SENTENCE)
        newSentence.sentence.opcode = sentence;
    else
        newSentence.sentence.guidance = sentence;

    return newSentence;
}

/*
 * Creates an argument node for the given data and data type.
 *
 * @param   data        The data to be stored in the argument node.
 * @param   dataType    The type of data being stored.
 *
 * @return  A pointer to the created argument node.
 */
arg_node_t *createArgumentNode(void *data, data_type_t dataType)
{
    /* Create the argument node. */
    arg_node_t *newArgNode = (arg_node_t *) allocate_space(sizeof(arg_node_t));

    /* Initialized its values. */
    newArgNode -> paramNum = UNKNOWN_NUMBER;
    newArgNode -> argData = createData(data, dataType);
    newArgNode -> addressingMethod = NO_ADD_METHOD;
    newArgNode -> nextArg = NULL;

    return newArgNode;
}

/*
 * Creates a data_t object with the given data and data type.
 *
 * @param   data        The data to be stored in the data_t object.
 * @param   dataType    The type of data being stored.
 *
 * @return  A data_t object containing the given data and data type.
 */
data_t createData(void *data, data_type_t dataType)
{
    data_t newData; /* Object to return. */
    newData.dataType = dataType;

    switch (dataType) /* Adding the data to the data_t object accordingly to its type. */
    {
        case INT:
            newData.data.num = *((short int *) data);
            break;
        case STRING: /* In case of string, duplicate it. */
            newData.data.string = my_strdup((char *)data);
            break;
        case REG:
            newData.data.reg = *((register_t *) data);
            break;
    }

    return newData;
}

/*
 * Adds an AST (Abstract Syntax Tree) to the AST list.
 *
 * @param   *astList Pointer to the AST list.
 * @param   **ast Pointer to the AST to add to the list.
 *
 * @return  0 if the node was successfully added to the list, 1 if the given list is empty.
 */
int addAstToList(ast_list_t *astList, ast_t **ast)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (astList != NULL) /* If the parameter is valid. */
    {
        ast_list_node_t *newAstListNode = createAstListNode(ast); /* Create a node for the ast. */
        if (astList -> head == NULL) /* If the list is empty. */
            astList -> head = astList -> tail = newAstListNode;
        else
        {
            astList -> tail -> next = newAstListNode; /* Add the new ast to the end of the list. */
            astList -> tail = newAstListNode; /* Fix the tail. */
        }

        returnCode = SUCCESS_CODE; /* New node added successfully to the list. */
    }

    return returnCode;
}

/*
 * Adds a label name to the AST.
 *
 * @param   ast         Pointer to the AST.
 * @param   labelName   Name of the label to add.
 */
void addLabelToAst(ast_t *ast, const char *labelName)
{
    ast -> label = my_strdup(labelName); /* Making a duplicate of the name and adding it. */
}

/*
 * Adds a sentence to the given Abstract Syntax Tree (AST).
 *
 * @param   ast The Abstract Syntax Tree.
 * @param   sentence The value of the sentence to add.
 * @param   sentenceType The type of sentence to add.
 */
void addSentenceToAst(ast_t *ast, int sentence, sentence_type_t sentenceType)
{
    /* Create the sentence of the sentence value. */
    sentence_t sentenceObj = createSentence(sentenceType, sentence);
    /* Create the sentence node. */
    sentence_node_t *newSentenceNode = createSentenceNode(sentenceObj);

    ast -> sentenceNode = newSentenceNode; /* Add the new node to the ast. */
}

/*
 * Adds an argument node to the given AST.
 *
 * @param   ast         The AST to which the argument node should be added.
 * @param   data        The data for the argument node.
 * @param   dataType    The data type of the data for the argument node.
 */
void addArgumentToAst(ast_t *ast, void *data, data_type_t dataType)
{
    arg_node_t *lastNode = gotoLastArgNode(ast); /* Finding the last argument node. */
    arg_node_t *newArgNode = createArgumentNode(data, dataType); /* Creating the new argument */
    newArgNode -> addressingMethod = findAddressingMethod(ast, dataType);

    if (lastNode == NULL) /* If there are no arguments currently in the ast. */
    {
        newArgNode -> paramNum = FIRST_ARG;
        ast -> sentenceNode -> argListHead = newArgNode;
    }
    else /* Add the new argument to the end of the arg list. */
    {
        newArgNode -> paramNum = lastNode -> paramNum + 1;
        lastNode -> nextArg = newArgNode;
    }
}

/*
 * Check if the given AST has a label.
 *
 * @param   ast         Pointer to the AST.
 * @return  TRUE if the AST has a label, otherwise FALSE.
 */
boolean isLabel(ast_t *ast)
{
    return (ast != NULL && ast -> label != NULL)? TRUE : FALSE;
}

/*
 * Finds the addressing method for the given AST and data type.
 *
 * @param   ast         The AST to be analyzed.
 * @param   dataType    The type of data being analyzed.
 *
 * @return  The addressing method to be used for the given data type in the AST.
 */
addressing_method_t findAddressingMethod(ast_t *ast, data_type_t dataType)
{
    /* Value to return. Assuming there is no addressing method, in this case
     * the ast represents a guidance sentence. */
    addressing_method_t addressingMethod = NO_ADD_METHOD;

    /* If the ast represents a direction sentence (there is an addressing method). */
    if (ast -> sentenceNode -> sentence.sentenceType == DIRECTION_SENTENCE)
        switch (dataType)
        {
            case INT: /* Instant value. */
                addressingMethod = INSTANT;
                break;
            case STRING: /* Label name. */
                addressingMethod = DIRECT;
                break;
            case REG: /* Register. */
                addressingMethod = DIRECT_REGISTER;
                break;
        }

    return addressingMethod;
}

/*
 * Gets the last argument node in the given AST.
 *
 * @param   ast The AST for which to find the last argument node.
 *
 * @return      A pointer to the last argument node in the AST,
 *              or NULL if the AST is empty or if there are no arguments.
 */
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

/*
 * Deletes the argument node and set the pointer to NULL.
 *
 * @param   pArgNode    A pointer to the argument node to be deleted.
 *
 * @return  0 on success, -1 if the given pointer is NULL.
 */
int deleteArgumentNode(arg_node_t **pArgNode)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (pArgNode != NULL && *pArgNode != NULL) /* If the parameter is valid */
    {
        if ((*pArgNode) -> argData.dataType == STRING) /* If the argument has a string. */
            (void) free_ptr(POINTER((*pArgNode) -> argData.data.string)); /* Free it. */
        (void) free_ptr(POINTER(*pArgNode)); /* Free the argument node itself. */

        returnCode = SUCCESS_CODE; /* Argument node deleted successfully. */
    }

    return returnCode;
}

/*
 * Deletes the argument list and set the pointer to NULL.
 *
 * @param   pArgList    A pointer to the head of the argument list to be deleted.
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteArgumentList(arg_node_t **pArgList)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (pArgList != NULL) /* If the parameter is valid */
    {
        arg_node_t *curr = *pArgList, *currDel = *pArgList; /* Helper nodes */

        while (curr != NULL) /* While there are more nodes to delete. */
        {
            curr = curr -> nextArg; /* Take curr node forward in the list. */
            (void) deleteArgumentNode(&currDel); /* Delete the current node. */
            currDel = curr; /* Take the currDel node forward in the list. */
        }

        returnCode = SUCCESS_CODE; /* Argument list deleted successfully. */
    }

    return returnCode;
}

/*
 * Deletes the AST and set the pointer to NULL.
 *
 * @param   pAst    A pointer to the AST to be deleted.
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAst(ast_t **pAst)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (pAst != NULL && *pAst != NULL) /* If the parameter is valid */
    {
        /* Deletes the arguments in the ast. */
        (void) deleteArgumentList(&((*pAst) -> sentenceNode -> argListHead));
        (void) free_ptr(POINTER((*pAst) -> sentenceNode)); /* Delete the sentence node. */
        (void) free_ptr(POINTER((*pAst) -> label)); /* Delete the label name */
        (void) free_ptr(POINTER(*pAst)); /* Delete the ast itself. */

        returnCode = SUCCESS_CODE; /* ast deleted successfully. */
    }

    return returnCode;
}

/*
 * Deletes the AST list node and set the pointer to NULL.
 *
 * @param   pAstListNode    A pointer to the AST list node to be deleted.
 *
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAstListNode(ast_list_node_t **pAstListNode)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (pAstListNode != NULL && *pAstListNode != NULL) /* If the parameter is valid */
    {
        (void) deleteAst(&((*pAstListNode) -> ast)); /* Delete the ast in the node. */
        (void) free_ptr(POINTER(*pAstListNode)); /* Delete the node itself. */

        returnCode = SUCCESS_CODE; /* node deleted successfully. */
    }

    return returnCode;
}

/*
 * Deletes the entire AST list and set the pointer to NULL.
 *
 * @param   pAstList    A pointer to the AST list to be deleted.
 *
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAstList(ast_list_t **pAstList)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (pAstList != NULL) /* If the parameter is valid */
    {
        /* Helper nodes. */
        ast_list_node_t *curr = (*pAstList) -> head, *currDel = (*pAstList) -> head;

        while (curr != NULL) /* While there are more nodes to delete. */
        {
            curr = curr -> next; /* Take curr node forward in the list. */
            (void) deleteAstListNode(&currDel); /* Delete the current node. */
            currDel = curr; /* Take the currDel node forward in the list. */
        }

        returnCode = SUCCESS_CODE; /* List deleted successfully. */
    }

    return returnCode;
}