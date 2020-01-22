#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/*
 * TODO add description
 * Allocate enough memory to hold a 2d array of the size numberOfLines * numberOfLines.
 *
 * @parameter A:
 * @parameter numberOfLines: 
 */
void initializeMatrix(Matrix *A, const int numberOfLines) {
	A->n = numberOfLines;

	A->data = malloc(numberOfLines * sizeof(double*));
	for(int i = 0; i < numberOfLines; i++) {
		A->data[i] = malloc(numberOfLines * sizeof(double));
	}
}

/*
 * Initializes the members of the Vector.
 */
void initializeVector(Vector *V, const int numberOfElements) {
	V->n = numberOfElements;

	V->data = malloc(numberOfElements * sizeof(double));
}

/*
 * Prints the passed Matrix in stdout.
 *
 * @parameter A: The Matrix that will have its data member printed.
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
 * @parameter V: The Vector that will have its data member printed.
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
 * @parameter A: The Matrix containing data that was allocated using malloc().
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
 * @parameter V: The Vector containing data that was allocated using malloc().
 */
void freeVector(Vector *V) {
	free(V->data);
	free(V);
}
