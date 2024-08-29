#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int result_code = OK;
  if (s21_matrix_exists(A) == 0) {
    result_code = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    result_code = INCORRECT_MATRIX;
  }
  return result_code;
}