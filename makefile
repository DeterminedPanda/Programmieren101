prog: main.o file_reader.o jacobi.o gauss_seidel.o
	gcc -Wall -pedantic-errors -o prog main.o file_reader.o jacobi.o gauss_seidel.o

main.o: main.c
	gcc -Wall -pedantic-errors main.c


file_reader.o: file_reader.c
	gcc -Wall -pedantic-errors file_reader.c


jacobi.o: jacobi.c
	gcc -Wall -pedantic-errors jacobi.c


gauss_seidel.o: gauss_seidel.c
	gcc -Wall -pedantic-errors gauss_seidel.c

clean:
	rm prog main.o file_reader.o jacobi.o gauss_seidel.o
