#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]) {

    time_t t;
    srand((unsigned) time(&t));

    matrix_t* mat = initialize_matrix(10, 5);

    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            mat->data[r][c] = (float) rand() / (float) RAND_MAX * 100.0f;
        }
    }


    printf("Original matrix: \n");
    show_matrix(mat);

    matrix_t* mat_t = transpose(mat);
    printf("Transposed matrix: \n");
    show_matrix(mat_t);

    matrix_t* mat_m = matmul(mat, mat_t);
    printf("mat*mat_t: \n");
    show_matrix(mat_m);

    delete_matrix(mat);
    delete_matrix(mat_t);
    delete_matrix(mat_m);

    return 0;
}