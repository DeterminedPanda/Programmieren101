#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file_reader.h"
#include "jacobi.h"
#include "gauss_seidel.h"

int main(void) {
	printf("Willkommen bei dem Jacobi-Verfahren und Gauß-Seidel-Verfahren Rechner von Justinas Maniscalco AI19B.\n");
	printf("Bitte geben Sie den relativen oder absoluten Pfad einer gültigen CSV Datei ein: ");
	char *fileName = readUserInput();
	Matrix *A = malloc(sizeof(Matrix));
	int error = readCSVFile(fileName, A);
	if(error == -1) {
		printf("Fehler: Die Datei konnte nicht geöffnet werden. Bitte stellen Sie sicher dass diese existiert und Leseberechtigung besteht.\n");
		exit(EXIT_FAILURE);
	} else {
		printf("Die Datei wurde erfolgreich eingelesen.\n");
	}
	free(fileName);

	return 0;
}

bool load(const char *filename, Matrix *A, Vector *b, Vector *x) {

	return false;
}

void solve (Method method, Matrix *A, Vector *b, Vector *x, double e) {
	if(method == GAUSS_SEIDEL) {
		calculateWithGaussSeidelMethod();
	} else if(method == JACOBI) {
		calculateWithJacobiMethod();
	} else {
		printf("Schwerwiegender Fehler: Die Ausgewählte Methode existiert nicht.\nBeende das Programm.\n");
		exit(EXIT_FAILURE);
	}
}
