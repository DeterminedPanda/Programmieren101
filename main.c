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
		int error = 0, numberOfLines = 0, userInput = 0;

		printf("Bitte geben Sie den relativen oder absoluten Pfad einer gültigen CSV Datei ein: ");
		char *fileName = readUserInput();
		error = getNumberOfLines(fileName, &numberOfLines);
		if(error == -1) {
			printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n\n");
			goto cleanup_fileName;
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
			goto cleanup_CSV;
		}

		error = isMatrixValid(A);
		if(error == -1) {
			printf("Fehler: Die Matrx A hat Nullen in der Diagonale.\n\n");
			goto cleanup_CSV;
		} else if(error == -2) {
			printf("Fehler: Die Matrix A ist nicht Diagonal Dominant.\n\n");
			goto cleanup_CSV;
		}


		userInput = askUserIterationMethod();
		if(userInput != 1 && userInput != 2) {
			printf("Ungültige Eingabe.\n\n");
			goto cleanup_CSV;
		}

		double epsilon = askUserEpsilon();
		struct VectorList *VL = solve(userInput - 1, A, b, x, epsilon);
		userInput = askUserOutputMethod();
		if(userInput == 1) {
			printVectorList(VL);	
		} else if(userInput == 2) {
			printVectorListTail(VL);
		} else {
			printf("Ungültige Eingabe.\n\n");
			goto cleanup_VectorList;
		}

cleanup_VectorList:
		freeVectorList(VL);

cleanup_CSV:
		freeMatrix(A);
		freeVector(b);
		freeVector(x);

cleanup_fileName:
		free(fileName);

		userInput = askUserRestart();
		if(userInput == 1) {
			continue;
		} else {
			break;
		}
	}

	return 0;
}

int askUserIterationMethod() {
	int userInput = 0;
	printf("Wählen Sie ein Iterationsverfahren aus, in dem Sie die korrespondierende Zahl eingeben:\n");
	printf("(1) Jacobi\n");
	printf("(2) Gauss-Seidel\n");
	printf("Ihr gewünschtes Iterationsverfahren: ");
	scanf("%d", &userInput);
	clearInputBuffer();

	return userInput;
}

double askUserEpsilon() {
	double userInput = 0.0;
	printf("Geben Sie nun eine Fehlerschranke ein (z.B. 1e-10): ");
	scanf("%lf", &userInput);
	clearInputBuffer();

	return userInput;
}

int askUserOutputMethod() {
	int userInput = 0;
	printf("Die Berechnung wurde durchgeführt. Wählen Sie aus wie viele Vektoren ausgegeben werden sollen, in dem Sie die korrespondierende Zahl eingeben:\n");
	printf("(1) Alle Vektoren\n");
	printf("(2) Nur der letzte Vektor\n");
	printf("Ihre gewünschte Ausgabe: ");
	scanf("%d", &userInput);
	clearInputBuffer();

	return userInput;
}

int askUserRestart() {
	int userInput = 0;
	printf("Soll eine neue Berechnung gestartet werden?\n");
	printf("(1) Ja\n");
	printf("(2) Nein\n");
	printf("Ihre Eingabe: ");
	scanf("%d", &userInput);
	clearInputBuffer();

	return userInput;
}

/*
 * Wrapper function of readCSVFile.
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
 *
 * @return struct VectorList: Returns a Linked List full of Vectors if the calclulations have been completed successfully. The pointer points to the first element of the Linked List.
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
