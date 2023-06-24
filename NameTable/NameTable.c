/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 *
 * Interface of a NameTable data structure.
 * The NameTable holds string names and for each name it's associated data.
 */

/* ---Include header files--- */
#include <stdlib.h>
#include "../new-data-types/boolean.h"
#include "../general_help_methods.h"
/* -------------------------- */

/* New data type 'dataType' which indicates which data type the name table holds. */
typedef enum {
    STRING_TYPE, /* Data type is (char *) */
    INT_TYPE /* Data type is (int) */
} dataType;

/* ---Macros--- */
/* ------------ */

/* ---Finals--- */
#define SUCCESS_CODE 0
#define TABLE_IS_NULL_CODE (-1)
#define NAME_ALREADY_IN_TABLE_CODE (-2)
#define NAME_NOT_IN_TABLE_CODE (-1)
#define NOT_MATCHING_DATA_CODE (-2)
/* ------------ */

/* Node of a linked list data type */
typedef struct Node {
    char *name; /* Name string */
    void *data; /* Data (char * or int) */
    struct Node *next; /* Pointer to the next node */
} Node;

/* NameTable data type - table of names and their data. */
typedef struct {
    dataType dataType; /* Type of data in the table */
    Node *head; /* Head node of the linked list */
} NameTable;

/*
 * Creates a new NameTable with the specified data type.
 *
 * @param   type The data type for the NameTable.
 * @return  Pointer to the newly created NameTable.
 */
NameTable *createNameTable(dataType type)
{
    NameTable *table = NULL;
    table -> dataType = type;
    table -> head = NULL;
    return table;
}

/*
 * Retrieves a node pointer based on the given name in the NameTable.
 *
 * @param   name_table Pointer to the NameTable.
 * @param   name The name to search for.
 * @return  The Node pointer if the name is found, otherwise NULL.
 */
Node *getNodeByName(const NameTable *name_table, const char *name)
{
    Node *curr = (name_table != NULL)? name_table -> head : NULL;

    /* Simple loop to traverse the linked list. */
    while (curr != NULL)
    {
        /* Exit the loop if we found the matching node */
        if (sameStrings(curr -> name, name) == TRUE) continue;
        curr = curr->next; /* Go to next node */
    }

    return curr;
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
        /* Take last node to the last node of the name table.
         * If the head is NULL, last node will also be NULL. */
        for (lastNode = name_table -> head;
            lastNode != NULL && lastNode -> next != NULL; lastNode = lastNode -> next);
    }

    return lastNode;
}

/*
 * Creates a node.
 *
 * @param   *name The name of the new node.
 * @param   *data The data of the new node.
 * @param   *next The next node connected to the new node.
 * @return  The newly created node.
 */
Node *createNode(char *name, void *data, Node *next)
{
    Node *new_node = NULL; /* New node, Node to return. */
    allocate_space(new_node, sizeof(Node));

    /* Assigns attributes of the new node */
    new_node -> name = name;
    new_node -> data = data;
    new_node -> next = next;

    return new_node;
}

/*
 * Checks if the given name exists in the NameTable.
 *
 * @param   table Pointer to the NameTable.
 * @param   name The name to check.
 * @return  TRUE if the name is found, otherwise FALSE.
 */
boolean isNameInTable(const NameTable *table, const char *name)
{
    return (getNodeByName(table, name) != NULL)? TRUE : FALSE;
}

/*
 * Adds a node to a given NameTable with its name.
 * If the table is NULL returns (-1).
 * If the name is already in the NameTable, returns (-2).
 *
 * @param   *name_table The table to insert the new node to.
 * @param   *name The name of the new node.
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
 * Gets the data associated with the given name in the NameTable.
 *
 * @param   table Pointer to the NameTable.
 * @param   name The name to retrieve the data for.
 * @return  Pointer to the data if found, otherwise NULL.
 */
void *getDataByName(const NameTable *table, const char *name)
{
    Node *node = getNodeByName(table, name); /* Find the node */
    return (node != NULL)? node -> data : NULL; /* Return its data if it's not NULL */
}

/*
 * Adds a given string to the data in the node associated with the given name in the NameTable.
 * Returns -1 if the name is not in the table.
 * Returns -2 if the table's data type is not string.
 *
 * @param   *name_table Pointer to the NameTable.
 * @param   *name The name of node to change the data for.
 * @param   *str The string to add to the data.
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
    else /* Add the string to the data */
        addTwoStrings((char **) &(node -> data), str);

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
 * @return  0 if successful, -1 if the data type is not (int), -2 if the
 *          name is not in the table.
 */
int setNumberInData(NameTable *name_table, const char *name, int num)
{
    int returnCode = SUCCESS_CODE; /* Value to return. */
    Node *node = getNodeByName(name_table, name); /* Get the node by name. */

    if (node == NULL) /* Check if the node exists. */
        returnCode = NAME_NOT_IN_TABLE_CODE;
    else if (name_table -> dataType != INT_TYPE) /* Check if the data type of table is string */
        returnCode = NOT_MATCHING_DATA_CODE;
    else /* Add the string to the data */
        *((int *) (node -> data)) = num;

    return returnCode;
}

/*
 * Deletes a given node.
 *
 * @param   *node The node to delete.
 */
void deleteNode(Node *node)
{
    if (node != NULL) /* Check if it is already deleted. */
    {
        (void) free_ptr(POINTER(node -> name));
        (void) free_ptr(POINTER(node -> data));
        (void) free_ptr(POINTER(node));
    }
}

/*
 * Deletes the entire NameTable and frees the memory.
 *
 * @param   table Pointer to the NameTable to delete.
 */
void deleteTable(NameTable *table)
{
    if (table != NULL) /* Check if it is already deleted. */
    {
        Node *curr = table -> head;
        while (curr != NULL) /* Delete it node-by-node. */
        {
            Node *next = curr->next;
            deleteNode(curr);
            curr = next;
        }
        table->head = NULL;
    }
}