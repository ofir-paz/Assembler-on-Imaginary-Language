/*
 * @author ofir
 * @version (21/06/23)
 *
 * Header file for the NameTable.c file.
 */

#ifndef MMN_14_NAMETABLE_H
#define MMN_14_NAMETABLE_H

#include "../new-data-types/boolean.h"

/* NameTable data type - table of names and their data. */
typedef struct NameTable NameTable;

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

/* ---------------Prototypes--------------- */

/*
 * Creates a new NameTable with the specified data type.
 *
 * @param   type The data type for the NameTable.
 *
 * @return  Pointer to the newly created NameTable.
 */
NameTable *createNameTable(dataType type);

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
int addNameToTable(NameTable *name_table, char *name);

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
int addStringToData(NameTable *name_table, const char *name, const char *str);

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
int setNumberInData(NameTable *name_table, const char *name, int num);

/*
 * Gets the data associated with the given name in the NameTable.
 *
 * @param   table Pointer to the NameTable.
 * @param   name The name to retrieve the data for.
 *
 * @return  Pointer to the data if found, otherwise NULL.
 */
name_data_t *getDataByName(const NameTable *table, const char *name);

/*
 * Checks if the given name exists in the NameTable.
 *
 * @param   *table  Pointer to the NameTable.
 * @param   *name    The name to check.
 *
 * @return  TRUE if the name is found, otherwise FALSE.
 */
boolean isNameInTable(const NameTable *table, const char *name);

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
int changeToPosAndAdd(NameTable *name_table, int add);

/*
 * Deletes the entire NameTable and frees the memory.
 *
 * @param   **table Pointer to the NameTable to delete.
 */
void deleteTable(NameTable **table);

void printIntTableList(NameTable *nameTableList[3]);

/* ---------------------------------------- */

#endif /* MMN_14_NAMETABLE_H */
