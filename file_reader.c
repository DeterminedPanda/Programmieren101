#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "file_reader.h"

/*
 * Reads and returns the user input from stdin.
 * The initial size of the array is 32 and will continously be doubled as long as the user input exceeds this limit.
 * Since the array is dynamically allocated (using malloc and realloc) the returned array has to be manually freed (using free).
 *
 * @return charArray: pointer to the first element of the char array.
 */
char* readUserInput() {
	int stringLength = 0;
	int mallocSize = 32; //expected string length is initially set to 32, will be doubled if exceeded.
	char *charArray = malloc(sizeof(char) * mallocSize);

	char currentChar;
	while((currentChar = fgetc(stdin)) != EOF && currentChar != '\n') {
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
 * Reads the specified CSV file into the Matrix A.
 * 
 * @parameter filePath: Path of the CSV file that is supposed to be read into A. May be an absolute or relative path.
 * @parameter A: Will contain the read CSV file.
 *
 * @return 0: Everything went fine. The File has been read into A.
 * @return -1: Couldn't read file. Permission denied error or file doesn't exists.
 */
int readCSVFile(const char *filePath, Matrix *A) {
	char *absolutePath = formatFilePath(filePath);
	printf("Current Directory: %s\n", absolutePath);

	//check if file exists and is readable	
	if(access(absolutePath, R_OK) == -1) {
		return -1;
	}

	int numberOfLines = 0;
	int returnCode = getNumberOfLines(absolutePath, &numberOfLines);
	if(returnCode == -1)
		return -1;

	/** 
	 * Rule conform CSV files have N amount of lines and N + 2 amount of rows.
	 * There have to be N + 2 columns, because of the coefficient "b" and the optional iteration vector "x" that are 
	 * included in the CSV files.
	 **/ 
	int numberOfColumns = numberOfLines + 2

	FILE *file = fopen(absolutePath, "r");
	if(file == NULL)
		return -1;

	char *line;
	size_t length;
	while((getline(&line, &length, file)) != -1) {
		double tuple[numberOfRows];
		char *token = strtok(line, ",");
		for(int i = 0; token != NULL, i++) {
			tuple[i] = atof(token);
			token = strtok(NULL, ",");
		}
		A->data = tuple;
		printf("Current line: %s\n", line);
	}

	return 0;
}

/**
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

/**
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

/**
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

	char *line;
	size_t length;
	while((getline(&line, &length, file)) != -1) {
		*numberOfLines++;
	}

	return 0;
}
