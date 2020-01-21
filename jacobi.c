#include <stdio.h>
#include "jacobi.h"

void calculateWithJacobiMethod(Matrix *A, Vector *b, Vector *x, double e) {
	int k = 0, maxIterations = 20, n = A->n;

	while(1) {
		if(k >= maxIterations) {
			break;
		}
		
		printf("%2d: ", k + 1);

		for(int i = 0; i < n; i++) {
			float sigma = 0.0;

			for(int j = 0; j < n; j++) {
				if(i != j) {
					sigma = sigma + A->data[i][j]*x->data[j];
				}
			}

			x->data[i] = (1/A->data[i][i]) * (b->data[i] - sigma);
			printf("%.10f ", x->data[i]);
		}
		printf("\n");
		k++;
	}
}
