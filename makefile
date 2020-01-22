prog: main.c file_reader.c data_structures.c gauss_seidel.c jacobi.c
	gcc -Wall -pedantic-errors -o prog main.c file_reader.c data_structures.c gauss_seidel.c jacobi.c

clean:
	rm prog
