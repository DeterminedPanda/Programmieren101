#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file_reader.h"
#include "jacobi.h"
#include "gauss_seidel.h"
#include "data_structures.h"

int main(void) {
	printf("Willkommen bei dem Jacobi-Verfahren und Gauß-Seidel-Verfahren Rechner von Justinas Maniscalco AI19B.\n");
	while(1) {
		printf("Bitte geben Sie den relativen oder absoluten Pfad einer gültigen CSV Datei ein: ");

		int error = 0, numberOfLines = 0;
		char *fileName = readUserInput();
		error = getNumberOfLines(fileName, &numberOfLines);
		if(error == -1) {
			printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n\n");
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
			printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n\n");
			continue;
		}


		int methodIndex = 0;
		printf("Wählen Sie ein Iterationsverfahren aus, in dem Sie die korrespondierende Zahl eingeben:\n");
		printf("(1) Jacobi\n");
		printf("(2) Gauss-Seidel\n");
		printf("Ihr gewünschtes Iterationsverfahren: ");
		scanf("%d", &methodIndex);
		clearInputBuffer();

		if(methodIndex != 1 && methodIndex != 2) {
			printf("Ungültige Eingabe.\n\n");
			continue;
		}

		double epsilon = 0.0;
		printf("Geben Sie nun eine Fehlerschranke ein (z.B. 1e-10): ");
		scanf("%lf", &epsilon);
		clearInputBuffer();

		struct VectorList *VL = solve(methodIndex - 1, A, b, x, epsilon);
		printVectorList(VL);

		//TODO this has to be put at the beginning of the loop, otherwise it might not be freed after continue has been executed.
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
 * @parameter fileName: The name or path of the file. The file format m
 * @parameter A: The Matrix containing the coefficients a.
 * @parameter b: The Vector containing the coefficients b.
 * @parameter x: The Vector containing the coefficients x.
 *
 * @return: Returns true if the file was successfully loaded into A, b and x. Otherwise false.
 */
bool load(const char *fileName, Matrix *A, Vector *b, Vector *x) {
	return readCSVFile(fileName, A, b, x) != -1;
}

/*
 * Solves the linear equation using the passed method (See the Method enumerator for a list of methods). 
 *
 * @parameter method: The method that will be used for the calculation of the linear equation.
 * @parameter A: The Matrix containing the coefficients a.
 * @parameter b: The Vector containing the coefficients b.
 * @parameter x: The Vector containing the coefficients x.
 * @parameter e: The approximation error.
 */
struct VectorList* solve (Method method, Matrix *A, Vector *b, Vector *x, double e) {
	if(method == GAUSS_SEIDEL) {
		printf("Führe die Gauss-Seidel Methode aus...\n");
		return calculateWithGaussSeidelMethod(A, b, x, e);
	} else if(method == JACOBI) {
		printf("Führe die Jacobi Methode aus...\n");
		return calculateWithJacobiMethod(A, b, x, e);
	} else {
		//Should never be executed.
		printf("Schwerwiegender Fehler: Die Ausgewählte Methode existiert nicht.\nBeende das Programm.\n");
		exit(EXIT_FAILURE);
	}
}
