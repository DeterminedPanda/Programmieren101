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
 * @return head: Returns the Vector Linked List containing all the iterations.
 */
struct VectorList* calculateWithGaussSeidelMethod(Matrix *A, Vector *b, Vector *x, double e) {
	int maxIterations = 100, n = A->n;
	Vector *xNew = malloc(sizeof(Vector));
	initializeVector(xNew, n);
	struct VectorList *head = malloc(sizeof(struct VectorList));
	initializeVectorList(head, xNew, NULL);
	struct VectorList *tail = head;

	for(int iteration = 0; iteration < maxIterations; iteration++) {
		bool convergence = true;

		for(int i = 0; i < n; i++) {
			double sum = 0;
			for(int j = 0; j < n; j++) {
				if(j != i) {
					sum += A->data[i][j] * xNew->data[j];
				}
			}
			xNew->data[i] = (1/A->data[i][i]) * (b->data[i] - sum);
			if(fabs(xNew->data[i] - x->data[i]) > e)
				convergence = false;
		}

		struct VectorList *current = malloc(sizeof(struct VectorList));
		Vector *V = malloc(sizeof(Vector));
		initializeVector(V, n);
		initializeVectorList(current, V, NULL);
		tail->next = current;
		tail = current;

		for(int i = 0; i < n; i++) {
			x->data[i] = xNew->data[i];
			current->V->data[i] = xNew->data[i];
		}

		if(convergence)
			break;
	}


	return head->next; //head is still pointing at tail, so we need to return head->next instead.
}
