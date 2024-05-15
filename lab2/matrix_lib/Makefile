CC=gcc
IDIR=include
CFLAGS=-I$(IDIR)
DYN_CFLAGS=$(CFLAGS) -Wall -fPIC -D_GNU_SOURCE

# BUILDING STATIC LIBRARY
%.o: %.c $(IDIR)/matrix.h
	$(CC) -c -o $@ $< $(CFLAGS)

lib_matrix.a: mat_mem.o mat_calc.o mat_utils.o
	ar r lib_matrix.a mat_mem.o mat_calc.o mat_utils.o

# BUILDING DYNAMIC LIBRARY
lib_matrixdyn.so: mat_calc_shared.o mat_mem_shared.o mat_utils_shared.o
	$(CC) mat_calc_shared.o mat_mem_shared.o mat_utils_shared.o -shared -o lib_matrixdyn.so

mat_calc_shared.o: mat_calc.c $(IDIR)/matrix.h
	$(CC) -c mat_calc.c -o mat_calc_shared.o $(DYN_CFLAGS)

mat_mem_shared.o: mat_mem.c $(IDIR)/matrix.h
	$(CC) -c mat_mem.c -o mat_mem_shared.o $(DYN_CFLAGS)

mat_utils_shared.o: mat_utils.c $(IDIR)/matrix.h
	$(CC) -c mat_utils.c -o mat_utils_shared.o $(DYN_CFLAGS)

.PHONY: clean

clean:
	rm *.o