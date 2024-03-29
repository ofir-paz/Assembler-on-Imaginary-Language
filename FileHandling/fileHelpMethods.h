/*
 * @author Ofir Paz
 * @version (27/04/2023)
 *
 * Header file for the fileHelpMethods.c file.
 */

#ifndef MMN_14_FILEHELPMETHODS_H
#define MMN_14_FILEHELPMETHODS_H

/* ---------------Prototypes--------------- */

/*
 * Opens a file.
 *
 * @param   *file_name The name of the file to open.
 * @param   *fileType The type of the file to open.
 * @param   *modeType The mode to open the file with.
 *
 * @return  Pointer to the opened file.
 */
FILE *openFile(const char *file_name, const char *fileType, const char *modeType);

/*
 * Closes a file.
 * Terminates the program on error!
 *
 * @param   **file Pointer to the file to close.
 */
void closeFile(FILE **file);

/* ---------------------------------------- */

#endif /* MMN_14_FILEHELPMETHODS_H */
