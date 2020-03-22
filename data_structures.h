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

struct VectorList {
	Vector *V;
	struct VectorList *next;
}; 

typedef enum {
	JACOBI = 0, GAUSS_SEIDEL = 1
} Method;

void initializeMatrix(Matrix *A, const int numberOfLines);
void initializeVector(Vector *V, const int numberOfElements);
void initializeVectorList(struct VectorList *VL, Vector *V, struct VectorList *next);
void printMatrix(Matrix *A);
void printVector(Vector *V);
void printVectorList(struct VectorList *VL);
void printVectorListTail(struct VectorList *VL);
void freeMatrix(Matrix *A);
void freeVector(Vector *V);
void freeVectorList(struct VectorList *VL);
#endif
