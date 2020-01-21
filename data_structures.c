#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/*
 * TODO add description
 * Allocate enough memory to hold a 2d array of the size array[numberOfLines][numberOfColumns]
 */
void initializeMatrix(Matrix *A, const int numberOfLines) {
	A->n = numberOfLines;

	A->data = malloc(numberOfLines * sizeof(double*));
	for(int i = 0; i < numberOfLines; i++) {
		A->data[i] = malloc(numberOfLines * sizeof(double));
	}
}

//TODO add description
void initializeVector(Vector *V, const int numberOfElements) {
	V->n = numberOfElements;

	V->data = malloc(numberOfElements * sizeof(double));
}

//TODO add description
void printMatrix(Matrix *A) {
	int n = A->n;

	printf("Matrix:\n");
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			printf("%f ", A->data[i][j]);
		}
		printf("\n");
	}
}

//TODO add description
void printVector(Vector *V) {
	int numberOfElements = V->n;

	printf("Vector:\n");
	for(int i = 0; i < numberOfElements; i++) {
		printf("%f ", V->data[i]);

		printf("\n");
	}
}

/* 
 * Frees the alloacted data in the Matrix.
 *
 * @parameter A: The Matrix that contains data that was alloacted using malloc().
 */
void freeMatrix(Matrix *A) {
	/*int numberOfLines = A->n;*/

	//TODO finish this its not working uwu
	/*for(int i = 0; i < numberOfLines; i++) {*/
		/*free(A[i]);*/
	/*}*/
	/*free(A);*/
}
