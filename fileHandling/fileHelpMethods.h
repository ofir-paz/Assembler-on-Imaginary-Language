/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the fileHelpMethods.c file.
 * */

#ifndef MMN_14_FILEHELPMETHODS_H
#define MMN_14_FILEHELPMETHODS_H

#include <stdio.h>

/* Opens a file.
 * Terminates the program on error!
 * param const char *file_name is the name of the file to open
 * param const char *fileType is the type of the file to open
 * param const char *modeType is the mode to open the file with
 * Returns a pointer to the opened file. */
FILE *openFile(const char *file_name, const char *fileType, const char *modeType);

/* Closes a file.
 * Terminates the program on error!
 * param FILE *file is the file to close
 * Returns nothing. */
void closeFile(FILE *file);

#endif /* MMN_14_FILEHELPMETHODS_H */
