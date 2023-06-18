/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * Header file for the writeToFile.c file.
 * */

#ifndef MMN_14_WRITETOFILE_H
#define MMN_14_WRITETOFILE_H

/* appends text to file.
 * param const char *file_name is the name of the file to append to
 * param const char *fileType is the type of the file to append to
 * param const char *text is the text to append to the wanted file
 * Return nothing. */
void appendToFile(const char *file_name, const char *fileType, const char *text);

#endif /* MMN_14_WRITETOFILE_H */
