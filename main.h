#ifndef MAIN_H 
#define MAIN_H
#include <stdbool.h>
#include "data_structures.h"

int askUserIterationMethod();
double askUserEpsilon();
int askUserOutputMethod();
int askUserRestart();
bool load (const char *filename, Matrix *A, Vector *b, Vector *x);
struct VectorList* solve (Method method, Matrix *A, Vector *b, Vector *x, double e);
#endif
