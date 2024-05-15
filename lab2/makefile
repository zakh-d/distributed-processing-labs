CC=gcc

lib_matrix.a:
	echo "lib_matrix.a file is not found in current directory"

main.o: main.c
	$(CC) -c main.c -I matrix_lib/include -o main.o

program: main.o lib_matrix.a
	$(CC) main.o lib_matrix.a -o program


program_dyn: main.o lib_matrixdyn.so
	$(CC) main.o -L. -l_matrixdyn -o program_dyn

.PHONY: clean

clean:
	rm *.o