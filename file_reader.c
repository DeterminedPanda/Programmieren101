#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "file_reader.h"

/*
 * Reads and returns the user input from stdin.
 * The initial size of the array is 32 and will continously be doubled as long as the user input exceeds this limit.
 * Since the array is dynamically allocated the returned array has to be manually freed.
 *
 * @return charArray: pointer to the first element of the char array.
 */
char* readUserInput() {
	int stringLength = 0;
	int mallocSize = 32; //expected string length is initially set to 32, will be doubled if exceeded.
	char *charArray = malloc(sizeof(char) * mallocSize);

	char currentChar;
	while((currentChar = getchar()) != '\n' && currentChar != EOF) {
		charArray[stringLength] = currentChar;
		stringLength++;

		if(stringLength == mallocSize) {
			mallocSize *= 2;
			charArray = realloc(charArray, mallocSize);
		}
	}

	charArray[stringLength] = '\0';

	return charArray;
}

/*
 * Clears the leftover characters from stdin.
 */
void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Reads the specified CSV file into the Matrix A, the Vector b and the Vector x.
 * 
 * @parameter filePath: Path of the CSV file that is supposed to be read into A. May be an absolute or relative path.
 * @parameter A: Will contain the read CSV file.
 *
 * @return 0: Everything went fine. The File has been read into A.
 * @return -1: Couldn't read file. Permission denied error or file doesn't exists.
 * @return -2: Aborted reading file, because a non number value was found in the CSV.
 */
int readCSVFile(const char *filePath, Matrix *A, Vector *b, Vector *x) {
	char *absolutePath = formatFilePath(filePath);
	printf("Derzeitige Datei: %s\n", absolutePath);

	//check if file exists and is readable	
	if(access(absolutePath, R_OK) == -1) {
		return -1;
	}

	/* 
	 * Rule conform CSV files have N amount of lines and N + 2 amount of rows.
	 * There have to be N + 2 columns, because of the coefficient "b" and the optional iteration vector "x" that are 
	 * included in the CSV files.
	 */ 
	int numberOfLines = (int) A->n, coefficientBIndex = numberOfLines, coefficientXIndex = numberOfLines + 1;

	FILE *file = fopen(absolutePath, "r");
	if(file == NULL)
		return -1;

	char *line = NULL;
	size_t length = 0;
	for(int currentLine = 0; (getline(&line, &length, file)) != -1; currentLine++) {

		char *token = strtok(line, ",");
		for(int currentColumn = 0; token != NULL; currentColumn++) {

			//omit newline character from token
			if(strstr(token, "\n") != NULL) {
				char *occurence = strstr(token, "\n");
				strncpy(occurence, "", 1);
			}

			if(currentColumn == coefficientBIndex) {
				b->data[currentLine] = atof(token);
			} else if(currentColumn == coefficientXIndex) {
				x->data[currentLine] = atof(token);
			} else {
				A->data[currentLine][currentColumn] = atof(token);
			}
			token = strtok(NULL, ",");
		}
	}

	fclose(file);

	return 0;
}

/*
 * Checks if the passed Matrix is dioganally dominant and if the diogana doesn't contain any zeros.
 *
 * @return 0: Matrix is valid.
 * @return -1: The Matrix contains zeros in its diagonal.
 * @return -2: The Matrix is not diagonally dominant.
 */
int isMatrixValid(Matrix *A) {
	if(!isDiagonalNonZero(A)) {
		return -1;
	} else if(!isDiagonalDominant(A)) {
		return -2;
	}

	return 0;
}

int isDiagonalDominant(Matrix *A) {
	int n = A->n;

	for(int i = 0; i < n; i++) {

		double sum = 0.0;
		for(int j = 0; j < n; j++) {
			if(j == i) 
				continue;

			sum += A->data[i][j];
		}

		if(A->data[i][i] < sum) {
			printf("---Diagonale innerhalb der Matrix an der Stelle %d %d ist nicht dominant.---\n", i+1, i+1);
			return 0;
		}
	}

	return 1;
}

int isDiagonalNonZero(Matrix *A) {
	int n = A->n;

	for(int i = 0; i < n; i++) {
		if(A->data[i][i] == 0) {
			printf("---Null innerhalb der Matrix an der Stelle %d %d gefunden.---\n", i+1, i+1);
			return 0;
		}
	}
	return 1;
}

/*
 * Formats the passed parameter filePath into an absolute file path.
 * I.e. path/to/file.csv would be transformed to /home/user/path/to/file.csv
 * If the passed parameter filePath is already an absolute file path, then it will simply returned without any changes.
 * Use isRelativePath if you aren't sure wether your file path is already an absolute file path or not.
 *
 * @parameter filePath: The file path that will be transformed into an absolute file path.
 *
 * @return: The absolute file path representation of filePath.
 */
char* formatFilePath(const char *filePath) {
	char *absolutePath = malloc(PATH_MAX);

	if(isRelativePath(filePath)) {
		//transform the relative path to an absolute path
		getcwd(absolutePath, PATH_MAX);
		strcat(absolutePath, "/");
		strcat(absolutePath, filePath);
	} else {
		strcpy(absolutePath, filePath);
	}

	return absolutePath;
}

/*
 * Checks if the passed path is a relative or absolute path. 
 * Absolute paths start with a backslash and relative paths dont.
 *
 * @parameter path: The to be checked path.
 * 
 * @return: Returns wether the passed parameter path is a relative path (true) or an absolute path (false).
 */
bool isRelativePath(const char *path) {
	return path[0] != '/';
}

/*
 * Counts the number of lines inside of a file that are seperated by the newline character "\n".
 *
 * @parameter filePath: The path to the file which will have it lines counted. The path can be absolute or relative.
 * @parameter numberOfLines: The number of lines inside of the passed file will be saved in this variable.
 *
 * @return -1: Couldn't read file. Permission denied error or file doesn't exists.
 * @return 0: The file was accessible and the number of lines has been counted.
 */
int getNumberOfLines(const char *filePath, int *numberOfLines) {
	char *absolutePath = formatFilePath(filePath);

	//check if file exists and is readable
	if(access(absolutePath, R_OK) == -1) {
		return -1;
	}

	FILE *file = fopen(absolutePath, "r");
	if(file == NULL)
		return -1;

	char *line = NULL;
	size_t length = 0;
	while((getline(&line, &length, file)) != -1) {
		*numberOfLines = *numberOfLines + 1;
	}

	fclose(file);

	return 0;
}
