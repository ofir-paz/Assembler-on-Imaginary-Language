/*
 * @author Ofir Paz
 * @version (28/07/2023)
 *
 * Header file for the assembler_ast.c file.
 */

#ifndef MMN_14_ASSEMBLER_AST_H
#define MMN_14_ASSEMBLER_AST_H

#include "../new-data-types/boolean.h"

/* Encapsulation is not harmed when including those finals since the purpose
 * of the ast is to diagnose line of assembly code, and a user that needs to use
 * the ast needs those finals as well. */
#include "encoding-finals/encoding_finals.h"

typedef enum {INT, STRING, REG} data_type_t;

/* ---------------Prototypes--------------- */

/* ---Data types prototypes--- */
typedef struct ast_list_t ast_list_t;
typedef struct ast_t ast_t;
typedef struct data_t data_t;
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
 * Creates a data_t object with the given data and data type.
 *
 * @param   data        The data to be stored in the data_t object.
 * @param   dataType    The type of data being stored.
 *
 * @return  A data_t object containing the given data and data type.
 */
data_t createData(void *data, data_type_t dataType);

/*
 * Adds an AST (Abstract Syntax Tree) to the AST list.
 *
 * @param   *astList Pointer to the AST list.
 * @param   **ast Pointer to the AST to add to the list.
 *
 * @return  0 if the node was successfully added to the list, 1 if the given list is empty.
 */
int addAstToList(ast_list_t *astList, ast_t **ast);

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
 * @param   sentenceType The type of sentence to add.
 * @param   statement The value of the statement to add.
 */
void addSentenceToAst(ast_t *ast, sentence_type_t sentenceType, int statement);

/*
 * Adds an argument node to the given AST.
 *
 * @param   ast         The AST to which the argument node should be added.
 * @param   data        The data for the argument node.
 * @param   dataType    The data type of the data for the argument node.
 */
void addArgumentToAst(ast_t *ast, void *data, data_type_t dataType);

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
 * Deletes the entire AST list and set the pointer to NULL.
 *
 * @param   pAstList    A pointer to the AST list to be deleted.
 *
 * @return  0 on success, -1 if the pointer is NULL.
 */
int deleteAstList(ast_list_t **pAstList);

/* ---------------------------------------- */

#endif /* MMN_14_ASSEMBLER_AST_H */
