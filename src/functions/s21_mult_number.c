#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int result_code = OK;
  if (s21_matrix_exists(A) == 0) {
    result_code = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    result_code = INCORRECT_MATRIX;
  }

  return result_code;
}