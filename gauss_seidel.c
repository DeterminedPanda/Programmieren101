#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gauss_seidel.h"

/*
 * Solves the linear equation using the Gauss-Seidel method.
 *
 * @parameter A: The Matrix containing the coefficients a.
 * @parameter b: The Vector containing the coefficients b.
 * @parameter x: The Vector containing the coefficients x.
 * @parameter e: The approximation error.
 *
 * @return head: //TODO
 */
struct VectorList* calculateWithGaussSeidelMethod(Matrix *A, Vector *b, Vector *x, double e) {
	int maxIterations = 100, n = A->n;
	Vector *xNew = malloc(sizeof(Vector));
	initializeVector(xNew, n);

	for(int iteration = 0; iteration < maxIterations; iteration++) {

		for(int i = 0; i < n; i++) {
			double sum1 = 0.0, sum2= 0.0;

			for(int j = 0; j < (i - 1); j++) {
				sum1 += A->data[i][j] * xNew->data[j];
			}

			for(int j = (i + 1); j < n; j++) {
				sum2 += A->data[i][j] * x->data[j]; 
			}

			xNew->data[i] = (1/A->data[i][i]) * (b->data[i] - sum1 - sum2);
		}

		for(int i = 0; i < n; i++) {
			x->data[i] = xNew->data[i];
		}

	}

	return NULL;
}



/*void lol() {*/

/*for(int iteration = 0; iteration < maxIterations; iteration++) {*/
/*bool convergence = true;*/


/*for(int i = 0; i < n; i++) {*/
/*double sum = 0.0;*/

/*for(int j = 0; j < i - 1; j++) {*/
/*sum += A->data[i][j] * xNew->data[j];*/
/*}*/

/*for(int j = i + 1; j < n; j++) {*/
/*sum += A->data[i][j] * x->data[j];*/
/*}*/

/*xNew->data[i] = (1/A->data[i][i]) * (b->data[i] - sum);*/

/*if(fabs(xNew->data[i] - x->data[i]) > e) {*/
/*convergence = false;*/
/*}*/
/*}*/

/*for(int i = 0; i < n; i++) {*/
/*x->data[i] = xNew->data[i];*/
/*}*/

/*printf("Iteration: %d ", iteration);*/
/*printVector(xNew);*/
/*if(convergence) */
/*break;*/
/*}*/

/*return NULL;*/
/*}*/
