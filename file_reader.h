#ifndef FILE_READER_H
#define FILE_READER_H
#include "main.h"

char* readUserInput();
int readCSVFile(const char *filePath, Matrix *A);
bool isRelativePath(const char *path);
char* formatFilePath(const char *filePath); 
int getNumberOfLines(const char *filePath, int *numberOfLines);
#endif
