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
#endif
