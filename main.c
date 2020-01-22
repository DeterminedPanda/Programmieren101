#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file_reader.h"
#include "jacobi.h"
#include "gauss_seidel.h"
#include "data_structures.h"

int main(void) {
	int error = 0;
	while(1) {
		printf("Willkommen bei dem Jacobi-Verfahren und Gauß-Seidel-Verfahren Rechner von Justinas Maniscalco AI19B.\n");
		printf("Bitte geben Sie den relativen oder absoluten Pfad einer gültigen CSV Datei ein: ");
		char *fileName = readUserInput();

		int numberOfLines = 0;
		error = getNumberOfLines(fileName, &numberOfLines);
		if(error == -1) {
			printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n");
			continue;
		}

		Matrix *A = malloc(sizeof(Matrix));
		initializeMatrix(A, numberOfLines);
		Vector *b = malloc(sizeof(Vector));
		initializeVector(b, numberOfLines);
		Vector *x = malloc(sizeof(Vector));
		initializeVector(x, numberOfLines);

		bool loadedSuccessfully = load(fileName, A, b, x);
		if(!loadedSuccessfully) {
			printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n");
			continue;
		}
		printMatrix(A);
		printVector(b);
		printVector(x);

		//TODO delete this
		solve(JACOBI, A, b, x, 1e-10);

		free(fileName);
		freeMatrix(A);
		freeVector(b);
		freeVector(x);
	}
	return 0;
}

/*
 * Wrapper Function, because honestly readCSVFile is a way better name than load.
 *
 * @parameter fileName:
 * @parameter A:
 * @parameter b:
 * @parameter x:
 *
 * @return: 
 */
bool load(const char *fileName, Matrix *A, Vector *b, Vector *x) {
	return readCSVFile(fileName, A, b, x) != -1;
}

/*
 * Solves the linear equation using the passed method (See the Method enumerator for a list of methods). 
 *
 * @parameter method:
 * @parameter A:
 * @parameter b:
 * @parameter x:
 * @parameter e:
 */
void solve (Method method, Matrix *A, Vector *b, Vector *x, double e) {
	if(method == GAUSS_SEIDEL) {
		printf("Führe die Gauss-Seidel Methode aus...\n");
		calculateWithGaussSeidelMethod(A, b, x, e);
	} else if(method == JACOBI) {
		printf("Führe die Jacobi Methode aus...\n");
		calculateWithJacobiMethod(A, b, x, e);
	} else {
		//Should never be executed.
		printf("Schwerwiegender Fehler: Die Ausgewählte Methode existiert nicht.\nBeende das Programm.\n");
		exit(EXIT_FAILURE);
	}
}
