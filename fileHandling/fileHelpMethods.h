//
// Created by ofir on 6/8/23.
//

#ifndef MMN_14_FILEHELPMETHODS_H
#define MMN_14_FILEHELPMETHODS_H

#include <stdio.h>

FILE *openFile(const char *file_name, const char *fileType, const char *modeType);

void closeFile(FILE *file);

#endif //MMN_14_FILEHELPMETHODS_H
