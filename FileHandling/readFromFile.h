/*
 * @author Ofir Paz
 * @version (18/08/2023)
 *
 * Header file for the readFromFile.c file.
 */

#ifndef MMN_14_READFROMFILE_H
#define MMN_14_READFROMFILE_H

#define UNABLE_TO_OPEN_FILE (-2)

/* ---------------Prototypes--------------- */

/*
 * Reads the next line from a given file.
 *
 * @param   *file_name      The name of the file to read from.
 * @param   *fileType       The type of the file to read from.
 * @param   **line          Pointer to string that will hold the read line.
 *
 * @return  The length of the line if it has been read successfully, EOF (-1) if the line
 *          was not read successfully, -2 if the file was not opened.
 */
int readNextLineFromFile(const char *file_name, const char *fileType, char **line);

/* ---------------------------------------- */

#endif /* MMN_14_READFROMFILE_H */
