/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * assembler_ast.c
 *
 * This file contains the implementation of the Abstract Syntax Tree (AST)
 * and functions to create, manipulate, and traverse the AST.
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../new-data-types/boolean.h"
#include "../encoding/encoding-finals/encoding_finals.h"
#include "../general-enums/assemblerFinals.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
/* -------------------------- */

/* ---Finals--- */
#define ZERO_INITIALIZE 0
#define SUCCESS_CODE 0
#define INVALID_GIVEN_PARAM_CODE (-1)
#define UNKNOWN_NUMBER 0
#define ZERO_ARGUMENTS 0
#define FIRST_ARG 1
/* ------------ */

/* ---Macros--- */
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
        reg_t reg;
    } data;
    data_type_t dataType; /* Will hold the type of data of the argument. */
} data_t; /* Will be the data of the argument (data; label name; register) */

/* This is an argument node type. will represent parameters of sentences. */
typedef struct arg_node_t
{
    unsigned short int paramNum; /* Current number of argument in sentence */
    data_t *argData;
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

/* List of abstract syntax trees. */
typedef struct
{
    ast_list_node_t *head;
    ast_list_node_t *tail;
    int counters[COUNTERS_AMOUNT];
} ast_list_t;

/* -------------------------------------------------- */

/* ---------------Prototypes--------------- */
addressing_method_t findAddressingMethod(ast_t *ast, data_type_t dataType);
arg_node_t *gotoLastArgNode(ast_t *ast);
boolean isLabel(ast_t *ast);
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
    /* Initializing it. */
    newAstList -> head = NULL;
    newAstList -> tail = NULL;
    newAstList -> counters[IC_] = ZERO_INITIALIZE;
    newAstList -> counters[DC_] = ZERO_INITIALIZE;

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
 * @param   *argData    The data to be stored in the argument node.
 *
 * @return  A pointer to the created argument node.
 */
arg_node_t *createArgumentNode(data_t *argData)
{
    /* Create the argument node. */
    arg_node_t *newArgNode = (arg_node_t *) allocate_space(sizeof(arg_node_t));

    /* Initialized its values. */
    newArgNode -> paramNum = UNKNOWN_NUMBER;
    newArgNode -> argData = argData;
    newArgNode -> addressingMethod = NO_ADD_METHOD;
    newArgNode -> nextArg = NULL;

    return newArgNode;
}

/*
 * Adds an AST (Abstract Syntax Tree) to the AST list.
 *
 * @param   *astList Pointer to the AST list.
 * @param   **ast Pointer to the AST to add to the list.
 *
 * @return  0 if the node was successfully added to the list, or -1 if the given list is empty.
 */
int addAstToList(ast_list_t *astList, ast_t **ast)
{
    int returnCode = INVALID_GIVEN_PARAM_CODE; /* Code to return, assume error. */

    if (astList != NULL && ast != NULL && *ast != NULL) /* If the parameters are valid. */
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
 * Gets a pointer to a specific counter.
 *
 * @param   *astList    The AST list that holds the counters.
 * @param   counter     Value indicating the required counter (0 for IC, 1 for DC).
 *
 * @return  pointer to the specific counter.
 */
int *getCounterPointer(ast_list_t *astList, int counter)
{
    return astList -> counters + counter;
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
    sentence_t sentenceObj = createSentence(sentence, sentenceType);
    /* Create the sentence node. */
    sentence_node_t *newSentenceNode = createSentenceNode(sentenceObj);

    ast -> sentenceNode = newSentenceNode; /* Add the new node to the ast. */
}

/*
 * Adds an argument node to the given AST.
 *
 * @param   ast         The AST to which the argument node should be added.
 * @param   *argData    The data for the argument node.
 */
void addArgumentToAst(ast_t *ast, data_t *argData)
{
    arg_node_t *lastNode = gotoLastArgNode(ast); /* Finding the last argument node. */
    arg_node_t *newArgNode = createArgumentNode(argData); /* Creating the new argument */
    newArgNode -> addressingMethod = findAddressingMethod(ast, argData -> dataType);

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
 * Retrieves the head node of the given AST list.
 *
 * @param   *astList    Pointer to the AST list.
 *
 * @return  The head node of the AST list, or NULL if the list is empty.
 */
ast_list_node_t *getAstHead(ast_list_t *astList)
{
    return astList -> head;
}

/*
 * Retrieves the next node in the given AST list.
 *
 * @param   *astListNode    Pointer to the current node.
 *
 * @return  The next node in the AST list, or NULL if the current node is the last.
 */
ast_list_node_t *getNextAstNode(ast_list_node_t *astListNode)
{
    return astListNode -> next;
}

/*
 * Retrieves the AST from the given AST list node.
 *
 * @param   *astListNode    Pointer to the AST list node.
 *
 * @return  Pointer to the AST associated with the given node.
 */
ast_t *getAst(ast_list_node_t *astListNode)
{
    return astListNode -> ast;
}

/*
 * Gets a duplicate of the label name from the given AST.
 *
 * @param   *ast The ast to get the label name from.
 *
 * @return  The label name in the given AST, or NULL if there is no label.
 */
char *getLabelName(ast_t *ast)
{
    return my_strdup(ast -> label);
}

/*
 * Finds if there are labels in the ast that needs to be added to a table.
 * Finds also which table the labels need to be added to.
 *
 * @param   *ast    The given ast to check the labels in.
 *
 * @return  NO_LABEL_TYPE if there are no labels to be added to tables in the ast,
 *          NORMAL if there is a normal label, ENTRY if there are labels to be added to
 *          an entry table, EXTERN if there are labels to be added to an extern table.
 */
label_type_t getLabelTypeForTable(ast_t *ast)
{
    label_type_t labelType = NO_LABEL_TYPE; /* Value to return, assume no labels. */

    if (isLabel(ast) == TRUE) /* If there is a label definition it's a normal label. */
        labelType = NORMAL;

    /* Check if there is a .entry or .extern guidance and set the value to return accordingly. */
    else if (ast -> sentenceNode -> sentence.sentenceType == GUIDANCE_SENTENCE)
    {
        if (ast -> sentenceNode -> sentence.sentence.guidance == ent)
            labelType = ENTRY;
        else if (ast -> sentenceNode -> sentence.sentence.guidance == ext)
            labelType = EXTERN;
    }

    return labelType;
}

/*
 * Gets the sentence from the given AST.
 *
 * @param   *ast The ast to get the sentence from.
 *
 * @return  The sentence from the given AST.
 */
sentence_t getSentence(ast_t *ast) {return ast -> sentenceNode -> sentence; }

/*
 * Gets the opcode from the Abstract Syntax Tree (AST).
 *
 * @param   *ast    The Abstract Syntax Tree to extract the opcode from.
 *
 * @return  The opcode extracted from the given AST.
 */
opcodes_t getOpcodeFromAST(ast_t *ast)
{
    opcodes_t opcode = NO_OPCODE;
    if (ast -> sentenceNode -> sentence.sentenceType == DIRECTION_SENTENCE)
        opcode = ast -> sentenceNode -> sentence.sentence.opcode;

    return opcode;
}

/*
 * Gets the guidance from the Abstract Syntax Tree (AST).
 *
 * @param   *ast    The Abstract Syntax Tree to extract the guidance from.
 *
 * @return  The guidance extracted from the given AST.
 */
guidance_t getGuidanceFromAST(ast_t *ast)
{
    guidance_t guidance = NO_GUIDANCE;
    if (ast -> sentenceNode -> sentence.sentenceType == GUIDANCE_SENTENCE)
        guidance = ast -> sentenceNode -> sentence.sentence.guidance;

    return guidance;
}

/*
 * Gets the argument list from the given AST.
 *
 * @param   *ast    The ast to get the argument list from.
 *
 * @return  The argument list from the given AST.
 */
arg_node_t *getArgList(ast_t *ast)
{
    return ast -> sentenceNode -> argListHead;
}

/*
 * Gets the next argument node from the given argument node.
 *
 * @param   *argNode    The argument node to get the next one from.
 *
 * @return  The next argument node from the given one, or NULL if the argument is NULL.
 */
arg_node_t *getNextNode(arg_node_t *argNode)
{
    return (argNode != NULL)? argNode -> nextArg : NULL;
}

/*
 * Gets the data from the given argument node.
 *
 * @param   *argNode    The node to extract the data from.
 *
 * @return  The data from the given argument node.
 */
data_t getArgData(arg_node_t *argNode)
{
    return *(argNode -> argData);
}

/*
 * Gets the addressing method for the given argument.
 *
 * @param   *argNode    The given argument to retrieve its addressing method.
 *
 * @return  The addressing method of the given argument, or 0 if the argument is NULL.
 */
addressing_method_t getArgAddressingMethod(arg_node_t *argNode)
{
    return (argNode != NULL)? argNode -> addressingMethod : ZERO_ADD_MTD;
}

/*
 * Gets the amount of arguments in the given AST.
 *
 * @param   *ast    The AST to get the amount of arguments from.
 *
 * @return  The amount of arguments in the given AST.
 */
unsigned short getArgAmount(ast_t *ast)
{
    arg_node_t *lastNode = gotoLastArgNode(ast);
    return (lastNode == NULL)? ZERO_ARGUMENTS : lastNode -> paramNum;
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
 * Deletes the label from the ast (if there is).
 *
 * @param   *ast    The ast with the label to delete.
 *
 * @return  0 on success, -1 if the label was NULL.
 */
int deleteLabel(ast_t *ast)
{
    int retCode = clear_ptr(ast -> label) /* Delete the label name (if there is). */
    return retCode;
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
        if ((*pArgNode) -> argData -> dataType == STRING) /* If the argument has a string, */
            {(void) clear_ptr((*pArgNode) -> argData -> data.string)} /* Free it. */

        (void) clear_ptr((*pArgNode) -> argData) /* Free the data of the arg. */
        (void) clear_ptr(*pArgNode) /* Free the argument node itself. */

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
        if ((*pAst) -> sentenceNode != NULL)
            (void) deleteArgumentList(&((*pAst) -> sentenceNode -> argListHead));
        (void) clear_ptr((*pAst) -> sentenceNode) /* Delete the sentence node. */
        (void) clear_ptr((*pAst) -> label) /* Delete the label name (if there is). */
        (void) clear_ptr(*pAst) /* Delete the ast itself. */

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
        (void) clear_ptr(*pAstListNode) /* Delete the node itself. */

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

    /* If the parameter is valid */
    if (pAstList != NULL && *pAstList != NULL && (*pAstList) -> head != NULL)
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

    (void) clear_ptr(*pAstList) /* Free the list itself. */

    return returnCode;
}

/* !!! -----DEBUGGING------IGNORE------- !!! */
/*
#include <stdio.h>

void printArgRec(arg_node_t *argNode)
{
    while (argNode != NULL)
    {
        switch (argNode->argData->dataType)
        {
            case INT:
                printf("\t[%d, I]=%9d", argNode->paramNum, argNode->argData->data.num);
                break;
            case STRING:
                printf("\t[%d, S]=%9s", argNode->paramNum, argNode->argData->data.string);
                break;
            case REG:
                printf("\t[%d, R]=%9d", argNode->paramNum, argNode->argData->data.reg);
                break;
        }
        argNode = argNode -> nextArg;
    }
}

void printAst(ast_t *ast)
{
    static int counter = 1;

    char *label = (ast -> label == NULL)? "___" : ast -> label;
    char *senType = (ast -> sentenceNode -> sentence.sentenceType == DIRECTION_SENTENCE)?
            "dir" : "gui";
    int command = (ast -> sentenceNode -> sentence.sentenceType == DIRECTION_SENTENCE)?
            ast -> sentenceNode -> sentence.sentence.opcode :
            ast -> sentenceNode -> sentence.sentence.guidance;

    printf("***\t%2d\tLabel=%8s\tsenType=%3s\tcmd=%2d", counter, label,
           senType, command);
    printArgRec(ast -> sentenceNode -> argListHead);
    puts("\t***");

    counter++;
}

void printAstList(ast_list_t *astList)
{
    ast_list_node_t *currAstNode = astList -> head;
    puts("\n*************************PRINTING AST*************************\n");
    printf("***\tIC=%4d\tDC=%4d\t***\n", astList -> counters[IC_], astList -> counters[DC_]);
    while (currAstNode != NULL)
    {
        printAst(currAstNode -> ast);
        currAstNode = currAstNode -> next;
    }

    puts("\n*************************FINISH PRINT AST*************************");
} */