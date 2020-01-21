#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
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

void initializeMatrix(Matrix *A, const int numberOfLines);
void initializeVector(Vector *V, const int numberOfElements);
void printMatrix(Matrix *A);
void printVector(Vector *V);
void freeMatrix(Matrix *A);
void freeVector(Vector *V);
#endif
