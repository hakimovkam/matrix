//
//  s21_matrix.c
//  
//
//  Created by Камиль Хакимов on 03.06.2023.
//

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err = 0;
    
    if (rows < 0 || columns < 0) {
        err = 1;
    } else {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double **)calloc(rows, sizeof(double *));
        
        if (result->matrix != NULL) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = (double *)calloc(columns, sizeof(double));
                
                if (result->matrix[i] == NULL) {
                    err = 1;
                    for (int j = 0; j < i; j++) {
                        free(result->matrix[j]);
                    }
                    
                    free(result->matrix);
                    result->matrix = NULL;
                    break;
                }
            }
        } else {
            err = 1;
        }
    }
    
    return err;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; ++i) {
            free(A->matrix[i]);
            A->matrix[i] = NULL;
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    
    if (A->rows) {
        A->rows = 0;
    }
    
    if (A->columns) {
        A->columns = 0;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int err = 0;
    int check_matrices_result = check_matrices(A, B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_result) {
        err = 1;
    }
    
    if (err != 1) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
                    err = 1;
                    break;
                }
            }
        }
    }
    return err;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = 0;
    int check_matrices_result = check_matrices(A, B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_result) {
        err = 1;
    }
    
    if (err != 1) {
        int rows = A->rows;
        int cols = A->columns;
        int creation_result = s21_create_matrix(rows, cols, result);
        
        if (creation_result == 0) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            err = 1;
        }
    }
    
    return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = 0;
    int check_matrices_result = check_matrices(A, B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_result) {
        err = 1;
    }
    
    if (err != 1) {
        int rows = A->rows;
        int cols = A->columns;
        int creation_result = s21_create_matrix(rows, cols, result);
        
        if (creation_result == 0) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        } else {
            err = 1;
        }
    }
    

    return err;
}

void print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%8.2f ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

int check_matrices(matrix_t* A, matrix_t* B) {
    int res_A = 0;
    if (A == NULL) {
        res_A = 1;
    } else if (A->rows <= 0 || A->columns <= 0) {
        res_A = 0;
    }

    int res_B = 0;
    if (B == NULL) {
        res_B = 1;
    } else if (B->rows <= 0 || B->columns <= 0) {
        res_B = 1;
    }
    
    int res = 0;
    if (res_A == 1 || res_B == 1) {
        res = 1;
    }
    
    return res;
}
