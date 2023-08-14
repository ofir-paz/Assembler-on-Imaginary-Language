/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * Interface of a NameTable data structure.
 * The NameTable holds string names and for each name it's associated data.
 */

/* ---Include header files--- */
#include <stddef.h>
#include "../new-data-types/boolean.h"
#include "../util/memoryUtil.h"
#include "../util/stringsUtil.h"
#include "../util/numberUtil.h"
/* -------------------------- */

/* ---Macros--- */
#define SWITCH_SIGN_AND_ADD(x, add) ((x) = (x) * (-1) + (add))
/* ------------ */

/* ---Finals--- */
#define SUCCESS_CODE 0
#define TABLE_IS_NULL_CODE (-1)
#define NAME_ALREADY_IN_TABLE_CODE (-2)
#define NAME_NOT_IN_TABLE_CODE (-1)
#define NOT_MATCHING_DATA_CODE (-2)
/* ------------ */

/* ---------------Name table--------------- */

/* New data type 'dataType' which indicates which data type the name table holds. */
typedef enum {
    STRING_TYPE, /* Data type is (char *) */
    INT_TYPE /* Data type is (int) */
} dataType;

typedef union
{
    char *string;
    int num;
} name_data_t; /* Data (char * or int) */

/* Node of a linked list data type */
typedef struct Node {
    char *name; /* Name string */
    name_data_t *data; /* Data (char * or int) */
    struct Node *next; /* Pointer to the next node */
} Node;

/* NameTable data type - table of names and their data. */
typedef struct {
    dataType dataType; /* Type of data in the table */
    Node *head; /* Head node of the linked list */
} NameTable;
/* ---------------------------------------- */


/* ---------------Prototypes--------------- */
Node *getNodeByName(const NameTable *name_table, const char *name);
boolean isNameInTable(const NameTable *table, const char *name);
Node *getToLastNode(const NameTable *name_table);
/* ---------------------------------------- */

/*
 * Creates a new NameTable with the specified data type.
 *
 * @param   type The data type for the NameTable.
 *
 * @return  Pointer to the newly created NameTable.
 */
NameTable *createNameTable(dataType type)
{
    NameTable *table = (NameTable *) allocate_space(sizeof(NameTable));
    table -> dataType = type;
    table -> head = NULL;
    return table;
}

/*
 * Creates a node for the name table.
 *
 * @param   *name       The name of the new node.
 * @param   nameData    The data of the new node.
 * @param   *next       The next node connected to the new node.
 *
 * @return  The newly created node.
 */
Node *createNode(char *name, name_data_t *nameData, Node *next)
{
    /* New node, Node to return. */
    Node *new_node = (Node *) allocate_space(sizeof(Node));

    /* Assigns attributes of the new node */
    new_node -> name = name;
    new_node -> data = nameData;
    new_node -> next = next;

    return new_node;
}

/*
 * Adds a node to a given NameTable with its name.
 * If the table is NULL returns (-1).
 * If the name is already in the NameTable, returns (-2).
 *
 * @param   *name_table The table to insert the new node to.
 * @param   *name The name of the new node.
 *
 * @return  0 on success, (-1) if the given table is NULL, (-2) if the name is already
 *          in the table.
 */
int addNameToTable(NameTable *name_table, char *name)
{
    int returnCode = SUCCESS_CODE; /* Value to return, assume the node will be added. */

    if (name_table == NULL) /* If the table doesn't exist. */
        returnCode = TABLE_IS_NULL_CODE;

        /* If the name is already in the table. */
    else if (isNameInTable(name_table, name) == TRUE)
        returnCode = NAME_ALREADY_IN_TABLE_CODE;

    else /* We can add the new node. */
    {
        Node *lastNode = getToLastNode(name_table); /* Last node of the linked list. */
        if (lastNode == NULL) /* Extreme case where's the list has no nodes yet. */
            name_table -> head = createNode(name, NULL, NULL);
        else
            lastNode -> next = createNode(name, NULL, NULL);
    }

    return returnCode;
}

/*
 * Adds a given string to the data in the node associated with the given name in the NameTable.
 * Returns -1 if the name is not in the table.
 * Returns -2 if the table's data type is not string.
 *
 * @param   *name_table Pointer to the NameTable.
 * @param   *name The name of node to change the data for.
 * @param   *str The string to add to the data.
 *
 * @return  0 if successful, -1 if the name is not in the table, -2 if the
 *          table's data type is not string.
 */
int addStringToData(NameTable *name_table, const char *name, const char *str)
{
    int returnCode = SUCCESS_CODE; /* Value to return. */
    Node *node = getNodeByName(name_table, name); /* Get the node by name. */

    if (node == NULL) /* Check if the node exists. */
        returnCode = NAME_NOT_IN_TABLE_CODE;
    else if (name_table -> dataType != STRING_TYPE) /* Check if the data type of table is string */
        returnCode = NOT_MATCHING_DATA_CODE;
    else if (node -> data == NULL) /* If the string in the data was empty before. */
    {
        node -> data = (name_data_t *) allocate_space(sizeof(name_data_t));
        node -> data -> string = my_strdup(str);
    }
    else /* Add the string to the data */
        addTwoStrings(&(node -> data -> string), str);

    return returnCode;
}

/*
 * Changes the data associated with the given name in the NameTable.
 * Returns -1 if the data type is not (int).
 * Returns -2 if the name is not in the table.
 *
 * @param   name_table Pointer to the NameTable.
 * @param   name The name of node to change the data for.
 * @param   num The new number to set the data to.
 *
 * @return  0 if successful, -1 if the data type is not (int), -2 if the
 *          name is not in the table.
 */
int setNumberInData(NameTable *name_table, const char *name, int num)
{
    int returnCode = SUCCESS_CODE; /* Value to return, assume success. */
    Node *node = getNodeByName(name_table, name); /* Get the node by name. */

    if (node == NULL) /* Check if the node exists. */
        returnCode = NAME_NOT_IN_TABLE_CODE;
    else if (name_table -> dataType != INT_TYPE) /* Check if the data type of table is string */
        returnCode = NOT_MATCHING_DATA_CODE;
    else /* Set the number in the data */
    {
        if (node -> data == NULL) /* If we need to allocate space in the memory. */
            node -> data = (name_data_t *) allocate_space(sizeof(name_data_t));
        node -> data -> num = num;
    }

    return returnCode;
}

/*
 * Retrieves a node pointer based on the given name in the NameTable.
 *
 * @param   name_table Pointer to the NameTable.
 * @param   name The name to search for.
 *
 * @return  The Node pointer if the name is found, otherwise NULL.
 */
Node *getNodeByName(const NameTable *name_table, const char *name)
{
    Node *curr = (name_table != NULL)? name_table -> head : NULL;

    /* Simple loop to traverse the linked list. */
    while (curr != NULL)
    {
        /* Exit the loop if we found the matching node */
        if (sameStrings(curr -> name, name) == TRUE) break;
        curr = curr->next; /* Go to next node */
    }

    return curr;
}

/*
 * Gets the data associated with the given name in the NameTable.
 *
 * @param   table Pointer to the NameTable.
 * @param   name The name to retrieve the data for.
 *
 * @return  Pointer to the data if found, otherwise NULL.
 */
name_data_t *getDataByName(const NameTable *table, const char *name)
{
    Node *node = getNodeByName(table, name); /* Find the node */
    return (node != NULL)? node -> data : NULL; /* Return its data if it's not NULL */
}

/*
 * Checks if the given name exists in the NameTable.
 *
 * @param   *table  Pointer to the NameTable.
 * @param   *name    The name to check.
 *
 * @return  TRUE if the name is found, otherwise FALSE.
 */
boolean isNameInTable(const NameTable *table, const char *name)
{
    return (getNodeByName(table, name) != NULL)? TRUE : FALSE;
}

/*
 * Finds the last node of the given linked list.
 *
 * @param   *name_table The given linked list to search for the last node in it.
 * @return  The last node of the linked list, or NULL if the list is empty or has the head
 *          node only.
 */
Node *getToLastNode(const NameTable *name_table)
{
    Node *lastNode = NULL; /* Node to return. */

    if (name_table != NULL)
    {
        /* Take lastNode to the last node of the name table.
         * If the head is NULL, lastNode will also be NULL. */
        for (lastNode = name_table -> head;
            lastNode != NULL && lastNode -> next != NULL; lastNode = lastNode -> next);
    }

    return lastNode;
}

/*
 * Changes all the negative numbers associated with different names in the table
 * To positive and adds them a given value.
 *
 * @param   *name_table     The given name table to change its elements.
 * @param   add             The value to add to the negative elements after they are changed
 *                          to positive.
 *
 * @return  0 on success, -1 if the given table is NULL, -2 if the given table is not INT type.
 */
int changeToPosAndAdd(NameTable *name_table, int add)
{
    int returnCode = SUCCESS_CODE; /* Value to return, assume success. */

    if (name_table == NULL)
        returnCode = TABLE_IS_NULL_CODE;

    else if (name_table -> dataType != INT_TYPE)
        returnCode = NOT_MATCHING_DATA_CODE;

    else
    {
        Node *currNode; /* Helper node. */

        /* Switch all negative elements to positive and add to them the value 'add'. */
        for (currNode = name_table -> head; currNode != NULL; currNode = currNode -> next)
            if (isNegative(currNode -> data -> num) == TRUE)
                SWITCH_SIGN_AND_ADD(currNode -> data -> num, add);
    }

    return returnCode;
}

/*
 * Gets a string to represent the given name table with int data type.
 * Assumes that each name in the name table is or less than 30 characters.
 *
 * @param   *nameTable  The name table to get a string representing it.
 *
 * @return  The string representing the name table.
 */
char *numbersNameTableToString(NameTable *nameTable)
{
    char *nameTableStr = NULL; /* String to return. */
    Node *currNode = nameTable -> head;

    while (currNode != NULL) /* Add all nodes to the string. */
    {
        addToStringInFormat(&nameTableStr, currNode -> name, currNode -> data->num);
        currNode = currNode -> next;
    }

    return nameTableStr;
}

/*
 * Deletes a given node.
 *
 * @param   *node           The node to delete.
 * @param   nodeDataType    The type of data stored in the node.
 */
void deleteNode(Node *node, dataType nodeDataType)
{
    if (node != NULL) /* Check if it is already deleted. */
    {
        (void) clear_ptr(node -> name)

        if (nodeDataType == STRING_TYPE && node -> data != NULL)
            {(void) clear_ptr(node -> data -> string)}

        (void) clear_ptr(node -> data)
        (void) clear_ptr(node)
    }
}

/*
 * Deletes the entire NameTable and frees the memory.
 *
 * @param   **table Pointer to the NameTable to delete.
 */
void deleteTable(NameTable **table)
{
    if (table != NULL && *table != NULL) /* Check if it is already deleted. */
    {
        Node *curr = (*table) -> head;
        while (curr != NULL) /* Delete it node-by-node. */
        {
            Node *next = curr->next;
            deleteNode(curr, (*table) -> dataType);
            curr = next;
        }
        (void) clear_ptr(*table)
    }
}

/* !!! -----DEBUGGING----- !!! */
#include <stdio.h>

void printIntTable(NameTable *name_table, char *tableName)
{
    Node *currNode = name_table -> head;
    printf("\n***************PRINTING TABLE: %s***************\n\n", tableName);

    while (currNode != NULL)
    {
        printf("***\tName: %6s\tval:%8d\t***\n", currNode->name, currNode->data->num);
        currNode = currNode -> next;
    }

    puts("\n***************FINISH PRINT TABLE***************");
}

void printIntTableList(NameTable *nameTableList[3])
{
    printIntTable(nameTableList[0], "normal");
    printIntTable(nameTableList[1], "entry");
    printIntTable(nameTableList[2], "extern");
}
