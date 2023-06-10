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
    int check_matrices_A = _check_matrices(A);
    int check_matrices_B = _check_matrices(B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_A || check_matrices_B) {
        err = 1;
    }
    
    if (!err) {
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
    int check_matrices_A = _check_matrices(A);
    int check_matrices_B = _check_matrices(B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_A || check_matrices_B) {
        err = 1;
    }
    
    if (!err) {
        int rows = A->rows;
        int cols = A->columns;
        err = s21_create_matrix(rows, cols, result);
        
        if (!err) {
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
    int check_matrices_A = _check_matrices(A);
    int check_matrices_B = _check_matrices(B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_A || check_matrices_B) {
        err = 1;
    }
    
    if (!err) {
        int rows = A->rows;
        int cols = A->columns;
        err = s21_create_matrix(rows, cols, result);
        
        if (!err) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        }
    }
    

    return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int err = 0;
    int check_matrices_A = _check_matrices(A);
    if (check_matrices_A) {
        err = 1;
    }
    
    if (!err) {
        int rows = A->rows;
        int cols = A->columns;
        err = s21_create_matrix(rows, cols, result);
        
        if (!err) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    }
    
    return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err = 0;
    int check_matrices_A = _check_matrices(A);
    int check_matrices_B = _check_matrices(B);
    if (A->rows != B->rows || A->columns != B->columns || check_matrices_A || check_matrices_B) {
        err = 1;
    }
    
    if (!err) {
        int rows = A->rows;
        int cols = A->columns;
        err = s21_create_matrix(rows, cols, result);
        
        if (!err) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * B->matrix[i][j];
                }
            }
        }
    }
    
    return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int err = _check_matrices(A);
    if (!err) {
        int rows = A->columns;
        int columns = A->rows;
        err = s21_create_matrix(rows, columns, result);
        if (!err) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[j][i] = A->matrix[i][j];
                }
            }
        }
    }
    
    return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int err = _check_matrices(A);
    if (!err) {
        err = s21_create_matrix(A->rows, A->columns, result);
        if (!err) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    matrix_t minor;
                    if (_minor(i+1, j+1, A, &minor) == 0) {
                        double minorDet;
                        if (s21_determinant(&minor, &minorDet) == 0) {
                            result->matrix[i][j] = pow(-1, i + j) * minorDet;
                        } else {
                            s21_remove_matrix(result);
                            err = 1;
                            break;
                        }
                        s21_remove_matrix(&minor);
                    } else {
                        s21_remove_matrix(result);
                        err = 1;
                        break;
                    }
                }
                if (err) {
                    break;
                }
            }
        }
    }
    return err;
}


int s21_determinant(matrix_t *A, double *result) {
    int err = _check_matrices(A);
    *result = 0.0;
    
    if (!err) {
        if (A->rows != A->columns) {
            err = 1;
        } else if (A->rows == 2) {
            *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
        } else {
            for (int i = 0; i < A->columns; i++) {
                matrix_t minor;
                if (_minor(1, i+1, A, &minor) == 0) {
                    double minorDet;
                    if (s21_determinant(&minor, &minorDet) == 0) {
                        *result += pow(-1, i) * A->matrix[0][i] * minorDet;
                    } else {
                        err = 1;
                    }
                    s21_remove_matrix(&minor);
                }
            }
        }
    }
    return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int err = _check_matrices(A);
    if (!err) {
        if (A->rows != A->columns) {
            err = 2;
        } else {
            double det;
            if (s21_determinant(A, &det) != 0 || det == 0) {
                err = 2;
            } else {
                matrix_t complements;
                err = s21_calc_complements(A, &complements);
                if (!err) {
                    err = s21_create_matrix(A->rows, A->columns, result);
                    if (!err) {
                        for (int i = 0; i < A->rows; i++) {
                            for (int j = 0; j < A->columns; j++) {
                                result->matrix[i][j] = complements.matrix[j][i] / det;
                            }
                        }
                    }
                    s21_remove_matrix(&complements);
                }
            }
        }
    } else {
        err = 1;
    }
    return err;
}

int _minor(int row, int column, matrix_t *A, matrix_t *result) {
    int err = 1;
    if (A->matrix != NULL) {
        err = s21_create_matrix(A->rows - 1, A -> columns - 1, result);
        if (err != 1) {
            int m, n = 0;
            for (int i = 0; i < A->rows; i++) {
                m = i;
                if (i > row - 1) {
                    m--;
                }
                for (int j = 0; j < A->columns; j++) {
                    n = j;
                    if (j > column - 1) {
                        n--;
                    }
                    if (i != row - 1 && j != column - 1) {
                        result->matrix[m][n] = A->matrix[i][j];
                    }
                }
            }
        }
    }
    return err;
}

double _calculate_determinant(matrix_t* A) {
    if (A->rows == 1) {
        return A->matrix[0][0];
    } else {
        double det = 0.0;

        for (int i = 0; i < A->columns; i++) {
            matrix_t minor;
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

            for (int j = 1; j < A->rows; j++) {
                int k = 0;

                for (int l = 0; l < A->columns; l++) {
                    if (l != i) {
                        minor.matrix[j - 1][k] = A->matrix[j][l];
                        k++;
                    }
                }
            }

            det += pow(-1.0, i) * A->matrix[0][i] * _calculate_determinant(&minor);
            s21_remove_matrix(&minor);
        }

        return det;
    }
}

void _print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%8.2f ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

int _check_matrices(matrix_t* A) {
    int res = 0;
    if (A == NULL) {
        res = 1;
    } else if (A->rows <= 0 || A->columns <= 0) {
        res = 1;
    }
    return res;
}
