#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void show_matrix(matrix_t* matrix) {
    if (matrix == NULL || matrix->data == NULL) {return;}

    for (int r = 0; r < matrix->rows; r++) {
        for (int c = 0; c < matrix->cols; c++) {
            printf(" %6.1f ", matrix->data[r][c]);
        }
        printf("\n");
    }
}
