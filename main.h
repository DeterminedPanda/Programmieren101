#include <stdbool.h>

#ifndef MAIN_H 
#define MAIN_H
typedef struct {
	int n;
	double **data;
} Matrix;

typedef struct {
	int n;
	double *data;
} Vector;

typedef enum {
	JACOBI = 0, GAUSS_SEIDEL = 1
} Method;

bool load (const char *filename, Matrix *A, Vector *b, Vector *x);
void solve (Method method, Matrix *A, Vector *b, Vector *x, double e);
#endif
