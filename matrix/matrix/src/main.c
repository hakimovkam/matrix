//
//  main.c
//  matrix
//
//  Created by Камиль Хакимов on 04.06.2023.
//

#include "s21_matrix.h"

int main(int argc, char *argv[]) {
    int rows = 5;
    int cols = 10;

    matrix_t first;
    int creation_result1 = s21_create_matrix(rows, cols, &first);

    if (creation_result1 == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                first.matrix[i][j] = 5;
            }
        }

        printf("first\n");
        print_matrix(&first);
    } else {
        printf("Ошибка при создании матрицы\n");
    }

    matrix_t second;
    int creation_result2 = s21_create_matrix(rows, cols, &second);

    if (creation_result2 == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                second.matrix[i][j] = 1;
            }
        }

        printf("second\n");
        print_matrix(&second);
    } else {
        printf("Ошибка при создании матрицы\n");
    }

    matrix_t result;
    int creation_result3 = s21_create_matrix(rows, cols, &result);

    if (creation_result3 == 0) {
        s21_sub_matrix(&first, &second, &result);
        
        printf("result\n");
        print_matrix(&result);
    }
//    s21_remove_matrix(&first);
//
//    if (my_matrix.matrix == NULL) {
//        printf("Матрица очищена\n");
//    } else {
//        printf("Ошибка при очистке матрицы\n");
//        print_matrix(&my_matrix);
//    }

    return 0;
}
