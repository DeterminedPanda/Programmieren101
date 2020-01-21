#ifndef MAIN_H 
#define MAIN_H
#include <stdbool.h>
#include "data_structures.h"

bool load (const char *filename, Matrix *A, Vector *b, Vector *x);
void solve (Method method, Matrix *A, Vector *b, Vector *x, double e);
#endif
