#ifndef FILE_READER_H
#define FILE_READER_H
#include "main.h"
#include <termios.h>

char* readUserInput();
void clearInputBuffer();
int readCSVFile(const char *filePath, Matrix *A, Vector *b, Vector *x);
bool isRelativePath(const char *path);
int isMatrixValid(Matrix *A);
int isDiagonalDominant(Matrix *A);
int isDiagonalNonZero(Matrix *A);
char* formatFilePath(const char *filePath); 
int getNumberOfLines(const char *filePath, int *numberOfLines);
void freeMatrix(Matrix *a);
#endif
