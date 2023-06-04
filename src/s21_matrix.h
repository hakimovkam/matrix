//
//  s21_matrix.h
//  
//
//  Created by Камиль Хакимов on 03.06.2023.
//

#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_
#define SUCCESS 1
#define FAILURE 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;


int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t* B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// MARK: -
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t * result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_comlements(matrix_t *A, matrix_t *result);
int s21_determinat(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void print_matrix(matrix_t *matrix);
int check_matrices(matrix_t* A, matrix_t* B);

#endif  // SRC_S21_MATRIX_H_