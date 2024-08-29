#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = OK;
  if (s21_matrix_exists(A) == 0 && s21_matrix_exists(B) == 0) {
    if (A->columns == B->rows) {
      result_code = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      result_code = CALC_ERROR;
    }
  } else {
    result_code = INCORRECT_MATRIX;
  }
  return result_code;
}