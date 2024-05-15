#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

matrix_t* initialize_matrix(int rows, int cols){
    matrix_t* matrix = (matrix_t*) malloc(sizeof(matrix_t));
    if (matrix == NULL) {
        fprintf(stderr, "memory was not allocated");
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (float**) malloc(rows * sizeof(float*));
    if (matrix->data == NULL) {
        free(matrix);
        fprintf(stderr, "memory was not allocated");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (float*) malloc(cols * sizeof(float));
        
        if (matrix->data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            fprintf(stderr, "memory was not allocated");
            return NULL;
        }
    }

    return matrix;
}

void delete_matrix(matrix_t* matrix)
{
    if (matrix == NULL || matrix->data == NULL) {return;}

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);
    free(matrix);
}