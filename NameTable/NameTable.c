/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file has the methods to write to files.
 * */

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
#define NOT_MATCHING_DATA_CODE (-1)
#define NAME_NOT_IN_TABLE_CODE (-2)
/* ------------ */

/* Node of a linked list data type */
typedef struct Node {
    char *name; /* Name string */
    void *data; /* Data (char * or int) */
    struct Node *next; /* Pointer to the next node */
} Node;

/* NameTable data type - table of names and their data. */
typedef struct {
    dataType type; /* Type of data in the table */
    Node *head; /* Head node of the linked list */
} NameTable;

/*
 * Creates a new NameTable with the specified data type.
 *
 * @param type The data type for the NameTable.
 * @return Pointer to the newly created NameTable.
 */
NameTable *createNameTable(dataType type) {
    NameTable *table = NULL;
    table -> type = type;
    table -> head = NULL;
    return table;
}

/*
 * Retrieves a node pointer based on the given name in the NameTable.
 *
 * @param name_table Pointer to the NameTable.
 * @param name The name to search for.
 * @return The Node pointer if the name is found, otherwise NULL.
 */
Node *getNodeByName(const NameTable *name_table, const char *name)
{
    Node *curr = name_table -> head;

    /* Simple loop to traverse the linked list. */
    while (curr != NULL)
    {
        /* Exit the loop if we found the matching node */
        if (sameStrings(curr->name, name) == TRUE) continue;
        curr = curr->next; /* Go to next node */
    }

    return curr;
}

/*
 * Checks if the given name exists in the NameTable.
 *
 * @param table Pointer to the NameTable.
 * @param name The name to check.
 * @return TRUE if the name is found, otherwise FALSE.
 */
boolean isNameInTable(const NameTable *table, const char *name)
{
    return (getNodeByName(table, name) != NULL)? TRUE : FALSE;
}

/*
 * Gets the data associated with the given name in the NameTable.
 *
 * @param table Pointer to the NameTable.
 * @param name The name to retrieve the data for.
 * @return Pointer to the data if found, otherwise NULL.
 */
void *getDataByName(const NameTable *table, const char *name)
{
    Node *node = getNodeByName(table, name); /* Find the node */
    return (node != NULL)? node -> data : NULL; /* Return its data if it's not NULL */
}

/*
 * Changes the data associated with the given name in the NameTable.
 * Returns -1 if the data type doesn't match the table's data type.
 * Returns -2 if the name is not in the table.
 *
 * @param table Pointer to the NameTable.
 * @param name The name to change the data for.
 * @param newData The new data to set.
 * @return 0 if successful, -1 if the data type doesn't match, -2 if the
 * name is not in the table.
 */
int changeData(NameTable *table, const char *name, void *newData)
{
    int returnCode; /* Value to return. */
    Node *node; /* Will point to the node with the matching given name (if there is). */
    if ()
     = getNodeByName(table, name);
    if ()

        if (table->type == INT_TYPE) {
            *((int *)(node->data)) = *((int *)(newData));
        } else {
            node->data = newData;
        }
        return 0;
    }
    return -1;
}

void deleteNode(Node *node)
{
    if (node != NULL)
    {
        (void) free_ptr(POINTER(node -> name));
        (void) free_ptr(POINTER(node -> data));
        (void) free_ptr(POINTER(node));
    }
}

/*
 * Deletes the entire NameTable and frees the memory.
 *
 * @param table Pointer to the NameTable to delete.
 */
void deleteTable(NameTable *table)
{
    if (table != NULL)
    {
        Node *curr = table -> head;
        while (curr != NULL)
        {
            Node *next = curr->next;
            deleteNode(curr);
            curr = next;
        }
        table->head = NULL;
    }
}