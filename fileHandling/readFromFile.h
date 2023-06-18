/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the readFromFile.c file.
 * */

#ifndef MMN_14_READFROMFILE_H
#define MMN_14_READFROMFILE_H

/* Reads the next line from a given file.
 * param const char *file_name is the name of the file to read from
 * param const char *fileType is the type of the file to read from
 * param char **line is a pointer to string that will hold the read line
 * Returns the length of the line if it has been read successfully or EOF (-1) if not. */
int readNextLineFromFile(const char *file_name, const char *fileType, char **line);

#endif /* MMN_14_READFROMFILE_H */
