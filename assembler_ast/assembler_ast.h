/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the assembler_ast.c file.
 */

#ifndef MMN_14_ASSEMBLER_AST_H
#define MMN_14_ASSEMBLER_AST_H

#include "../new-data-types/boolean.h"

/* Encapsulation is not harmed when including those finals since the purpose
 * of the ast is to diagnose line of assembly code, and a user that needs to use
 * the ast needs those finals as well. */
#include "../encoding/encoding-finals/encoding_finals.h"

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

/* ---Function return codes--- */
#define SUCCESS_CODE 0
#define INVALID_GIVEN_PARAM_CODE (-1)
/* --------------------------- */

/* ---------------Prototypes--------------- */

/* ---Data types prototypes--- */
typedef struct ast_list_t ast_list_t;
typedef struct ast_list_node_t ast_list_node_t;
typedef struct ast_t ast_t;
typedef struct arg_node_t arg_node_t;
/* --------------------------- */

/*
 * Creates an empty AST (Abstract Syntax Tree) list.
 *
 * @return  ast_list_t* A pointer to the newly created ast list.
 */
ast_list_t *createAstList(void );

/*
 * Creates a new AST (Abstract Syntax Tree) to represent a line of assembly code.
 *
 * @return  A pointer to the newly created AST.
 */
ast_t *creatAst(void );

/*
 * Adds an AST (Abstract Syntax Tree) to the AST list.
 *
 * @param   *astList Pointer to the AST list.
 * @param   **ast Pointer to the AST to add to the list.
 *
 * @return  0 if the node was successfully added to the list, or -1 if the given list is empty.
 */
int addAstToList(ast_list_t *astList, ast_t **ast);

/*
 * Gets a pointer to a specific counter.
 *
 * @param   *astList    The AST list that holds the counters.
 * @param   counter     Value indicating the required counter (0 for IC, 1 for DC).
 *
 * @return  pointer to the specific counter.
 */
int *getCounterPointer(ast_list_t *astList, int counter);

/*
 * Adds a label name to the AST.
 *
 * @param   ast         Pointer to the AST.
 * @param   labelName   Name of the label to add.
 */
void addLabelToAst(ast_t *ast, const char *labelName);

/*
 * Adds a sentence to the given Abstract Syntax Tree (AST).
 *
 * @param   ast The Abstract Syntax Tree.
 * @param   sentence The value of the sentence to add.
 * @param   sentenceType The type of sentence to add.
 */
void addSentenceToAst(ast_t *ast, int sentence, sentence_type_t sentenceType);

/*
 * Adds an argument node to the given AST.
 *
 * @param   ast         The AST to which the argument node should be added.
 * @param   *argData    The data for the argument node.
 */
void addArgumentToAst(ast_t *ast, data_t *argData);

/*
 * Retrieves the head node of the given AST list.
 *
 * @param   *astList    Pointer to the AST list.
 *
 * @return  The head node of the AST list, or NULL if the list is empty.
 */
ast_list_node_t *getAstHead(ast_list_t *astList);

/*
 * Retrieves the next node in the given AST list.
 *
 * @param   *astListNode    Pointer to the current node.
 *
 * @return  The next node in the AST list, or NULL if the current node is the last.
 */
ast_list_node_t *getNextAstNode(ast_list_node_t *astListNode);

/*
 * Retrieves the AST from the given AST list node.
 *
 * @param   *astListNode    Pointer to the AST list node.
 *
 * @return  Pointer to the AST associated with the given node.
 */
ast_t *getAst(ast_list_node_t *astListNode);

/*
 * Gets a duplicate of the label name from the given AST.
 *
 * @param   *ast The ast to get the label name from.
 *
 * @return  The label name in the given AST, or NULL if there is no label.
 */
char *getLabelName(ast_t *ast);

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
label_type_t getLabelTypeForTable(ast_t *ast);

/*
 * Gets the sentence from the given AST.
 *
 * @param   *ast The ast to get the sentence from.
 *
 * @return  The sentence from the given AST.
 */
sentence_t getSentence(ast_t *ast);

/*
 * Gets the opcode from the Abstract Syntax Tree (AST).
 *
 * @param   *ast    The Abstract Syntax Tree to extract the opcode from.
 *
 * @return  The opcode extracted from the given AST.
 */
opcodes_t getOpcodeFromAST(ast_t *ast);

/*
 * Gets the guidance from the Abstract Syntax Tree (AST).
 *
 * @param   *ast    The Abstract Syntax Tree to extract the guidance from.
 *
 * @return  The guidance extracted from the given AST.
 */
guidance_t getGuidanceFromAST(ast_t *ast);

/*
 * Gets the argument list from the given AST.
 *
 * @param   *ast    The ast to get the argument list from.
 *
 * @return  The argument list from the given AST.
 */
arg_node_t *getArgList(ast_t *ast);

/*
 * Gets the next argument node from the given argument node.
 *
 * @param   *argNode    The argument node to get the next one from.
 *
 * @return  The next argument node from the given one, or NULL if the argument is NULL.
 */
arg_node_t *getNextNode(arg_node_t *argNode);

/*
 * Gets the data from the given argument node.
 *
 * @param   *argNode    The node to extract the data from.
 *
 * @return  The data from the given argument node.
 */
data_t getArgData(arg_node_t *argNode);

/*
 * Gets the addressing method for the given argument.
 *
 * @param   *argNode    The given argument to retrieve its addressing method.
 *
 * @return  The addressing method of the given argument, or 0 if the argument is NULL.
 */
addressing_method_t getArgAddressingMethod(arg_node_t *argNode);

/*
 * Gets the amount of arguments in the given AST.
 *
 * @param   *ast    The AST to get the amount of arguments from.
 *
 * @return  The amount of arguments in the given AST.
 */
unsigned short getArgAmount(ast_t *ast);

/*
 * Check if the given AST has a label.
 *
 * @param   ast         Pointer to the AST.
 * @return  TRUE if the AST has a label, otherwise FALSE.
 */
boolean isLabel(ast_t *ast);

/*
 * Finds the addressing method for the given AST and data type.
 *
 * @param   ast         The AST to be analyzed.
 * @param   dataType    The type of data being analyzed.
 *
 * @return  The addressing method to be used for the given data type in the AST.
 */
addressing_method_t findAddressingMethod(ast_t *ast, data_type_t dataType);

/*
 * Deletes the label from the ast (if there is).
 *
 * @param   *ast    The ast with the label to delete.
 *
 * @return  0 on success, -1 if the label was NULL.
 */
int deleteLabel(ast_t *ast);

/*
 * Deletes the AST and set the pointer to NULL.
 *
 * @param   pAst    A pointer to the AST to be deleted.
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAst(ast_t **pAst);

/*
 * Deletes the entire AST list and set the pointer to NULL.
 *
 * @param   pAstList    A pointer to the AST list to be deleted.
 *
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAstList(ast_list_t **pAstList);

/*

 FUNCTIONS FOR DEBUGGING --- IGNORE

void printAst(ast_t *ast);
void printAstList(ast_list_t *astList);
*/
/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_AST_H */
