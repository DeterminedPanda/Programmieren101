#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "jacobi.h"

/*
 * Solves the linear equation using the Jacobi method. Will stop if the convergence or the max. iteration
 * number of 100 has been reached. The Linked List has been allocated using malloc, so the memory has to be manually
 * freed.
 *
 * @parameter A: The Matrix containing the coefficients a.
 * @parameter b: The Vector containing the coefficients b.
 * @parameter x: The Vector containing the coefficients x.
 * @parameter e: The approximation error.
 *
 * @return head: Returns the Vector Linked List containing all the iterations.
 */
struct VectorList* calculateWithJacobiMethod(Matrix *A, Vector *b, Vector *x, double e) {
	int maxIterations = 100, n = A->n;
	Vector *xNew = malloc(sizeof(Vector));
	initializeVector(xNew, n);
	struct VectorList *head = malloc(sizeof(struct VectorList));
	initializeVectorList(head, xNew, NULL);
	struct VectorList *tail = head;

	for(int iteration = 0; iteration < maxIterations; iteration++) {
		bool convergence = true;
		for(int i = 0; i < n; i++) { //loop of equations

			double sum = 0.0;
			for(int j = 0; j < n; j++) //loop of summation
				if(j != i)
					sum += A->data[i][j] * x->data[j];

			xNew->data[i] = -1 / A->data[i][i] * (sum - b->data[i]);
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
