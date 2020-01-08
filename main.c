#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file_reader.h"

int main(void) {
	/*printf("Willkommen bei dem Jacobi-Verfahren und Gauß-Seidel-Verfahren Rechner von Justinas Maniscalco AI19B.\n");*/
	/*printf("Bitte geben Sie den relativen oder absoluten Pfad einer gültigen CSV Datei ein: ");*/
	/*char *fileName = readUserInput();*/
	/*int error = readCSVFile(fileName, NULL);*/
	/*printf("%d ? 0 = ok, -1 = bad", error);*/
	/*free(fileName);*/

	//TODO delete
	char fileName = {"testdaten/konv3.csv"};
	printf("%s\n", fileName);
	return 0;
}

bool load(const char *filename, Matrix *A, Vector *b, Vector *x) {

	return false;
}

void solve (Method method, Matrix *A, Vector *b, Vector *x, double e) {

}
