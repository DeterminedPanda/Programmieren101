#ifndef FILE_READER_H
#define FILE_READER_H
#include "main.h"

char* readUserInput();
int readCSVFile(const char *filePath, Matrix *A, Vector *b, Vector *x);
bool isRelativePath(const char *path);
char* formatFilePath(const char *filePath); 
int getNumberOfLines(const char *filePath, int *numberOfLines);
void freeMatrix(Matrix *a);
#endif
