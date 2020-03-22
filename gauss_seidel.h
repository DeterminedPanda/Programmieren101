#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H
#include "data_structures.h"

struct VectorList* calculateWithGaussSeidelMethod(Matrix *A, Vector *b, Vector *x, double e);
#endif
