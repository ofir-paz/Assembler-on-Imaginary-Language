/*
 * @author Ofir Paz
 * @Version (18/08/2023)
 *
 * Header file for the writeToFile.c file.
 */

#ifndef MMN_14_WRITETOFILE_H
#define MMN_14_WRITETOFILE_H

/* ---------------Prototypes--------------- */

/*
 * Writes text to a given file.
 *
 * @param   *file_name      The name of the file to write to.
 * @param   *fileType       The type of the file to write to.
 * @param   *text           The text to write to the wanted file.
 */
void writeToFile(const char *file_name, const char *fileType, const char *text);

/* ---------------------------------------- */

#endif /* MMN_14_WRITETOFILE_H */
