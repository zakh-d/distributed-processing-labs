typedef struct matrix matrix_t;

struct matrix {
    int rows;
    int cols;
    float** data;
};

/* matrix memory handling */
matrix_t* initialize_matrix(int rows, int cols);
void delete_matrix(matrix_t* matrix);


/* 
    calculations on matrices 
    all functions allocate new matrix
*/
matrix_t* transpose(matrix_t* from);
matrix_t* matmul(matrix_t* mat1, matrix_t* mat2);
matrix_t* matadd(matrix_t* mat1, matrix_t* mat2);


/* matrix utils */
void show_matrix(matrix_t* matrix);