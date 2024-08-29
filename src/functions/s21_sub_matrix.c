#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_code = OK;
  if (s21_matrix_exists(A) == 0 && s21_matrix_exists(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      result_code = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
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
