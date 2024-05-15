#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>



matrix_t* transpose(matrix_t* from)
{
    matrix_t* transposed = initialize_matrix(from->cols, from->rows);

    for (int i = 0; i < from->rows; i++) {
        for (int j = 0; j < from->cols; j++) {
            transposed->data[j][i] = from->data[i][j];
        }
    }

    return transposed;
}

matrix_t* matmul(matrix_t* mat1, matrix_t* mat2) {

    if (mat1->cols != mat2->rows) {
        
        fprintf(stderr, "cannot multiply matrix with dimentions %dx%d and %dx%d", 
                        mat1->rows, mat1->cols, mat2->rows, mat2->cols);

        return NULL;
    }

    matrix_t* resulting_mat = initialize_matrix(mat1->rows, mat2->cols);
    for (int r = 0; r < resulting_mat->rows; r++) {
        for (int c = 0; c < resulting_mat->cols; c++) {
            resulting_mat->data[r][c] = 0;

            for (int i = 0; i < mat1->cols; i++) {
                resulting_mat->data[r][c] += mat1->data[r][i] * mat2->data[i][c];
            }
        }
    }
    return resulting_mat;
}

matrix_t* matadd(matrix_t* mat1, matrix_t* mat2) {
    
        if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
            fprintf(stderr, "cannot add matrix with dimentions %dx%d and %dx%d", 
                            mat1->rows, mat1->cols, mat2->rows, mat2->cols);
            return NULL;
        }
    
        matrix_t* resulting_mat = initialize_matrix(mat1->rows, mat1->cols);
        for (int r = 0; r < resulting_mat->rows; r++) {
            for (int c = 0; c < resulting_mat->cols; c++) {
                resulting_mat->data[r][c] = mat1->data[r][c] + mat2->data[r][c];
            }
        }
        return resulting_mat;
}