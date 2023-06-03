//
//  s21_matrix.c
//  
//
//  Created by Камиль Хакимов on 03.06.2023.
//

#include "s21_matrix.h"

int main(int argc, char *argv[]) {
    int rows = 5;
    int cols = 10;

    matrix_t my_matrix;
    int creation_result = s21_create_matrix(rows, cols, &my_matrix);

    if (creation_result == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                my_matrix.matrix[i][j] = i * cols + j;
            }
        }

        print_matrix(&my_matrix);
    } else {
        printf("Ошибка при создании матрицы\n");
    }

    s21_remove_matrix(&my_matrix);

    if (my_matrix.matrix == NULL) {
        printf("Матрица очищена\n");
    } else {
        printf("Ошибка при очистке матрицы\n");
        print_matrix(&my_matrix);
    }

    return 0;
}



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
        A->rows = 0
    }
    
    if (A->columns) {
        A->columns = 0
    }
}


void print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%8.2f ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}
