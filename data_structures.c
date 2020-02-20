#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/*
 * Initializes the passed Matrix by allocating a 2d with the dimensions numberOfLines * numberOfLines.
 * The 2d array is dynamically allocated and therefore needs to be freed manually.
 * The freeMatrix function can be used for this.
 *
 * @parameter A: The Matrix that will be initialized.
 * @parameter numberOfLines: The number of lines that will also be the number of columns in the 2d array.
 */
void initializeMatrix(Matrix *A, const int numberOfLines) {
	A->n = numberOfLines;

	A->data = malloc(numberOfLines * sizeof(double*));
	for(int i = 0; i < numberOfLines; i++) {
		A->data[i] = malloc(numberOfLines * sizeof(double));
	}
}

/*
 * Initializes the members of the Vector dynamically and therefore needs to be freed manually.
 * The freeVector function can be used for this.
 */
void initializeVector(Vector *V, const int numberOfElements) {
	V->n = numberOfElements;

	V->data = malloc(numberOfElements * sizeof(double));
}

/*
 * Prints the passed Matrix in stdout.
 *
 * @parameter A: The Matrix that will have its member "data" printed.
 */
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

/*
 * Prints the passed Vector in stdout.
 *
 * @parameter V: The Vector that will have its member "data" printed.
 */
void printVector(Vector *V) {
	int numberOfElements = V->n;

	printf("Vector:\n");
	for(int i = 0; i < numberOfElements; i++) {
		printf("%f ", V->data[i]);

		printf("\n");
	}
}

/* 
 * Frees the allocated data in the Matrix.
 *
 * @parameter A: The Matrix that will have its memory freed.
 */
void freeMatrix(Matrix *A) {
	int numberOfLines = A->n;

	for(int i = 0; i < numberOfLines; i++) {
		free(A->data[i]);
	}

	free(A);
}

/*
 * Frees the allocated data in the Vector.
 *
 * @parameter V: The Vector that will have its memory freed.
 */
void freeVector(Vector *V) {
	free(V->data);
	free(V);
}
