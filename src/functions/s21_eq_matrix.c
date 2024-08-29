#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result_code = SUCCESS;
  if (A->rows != B->rows) {
    result_code = FAILURE;
  } else if (A->columns != B->columns) {
    result_code = FAILURE;
  }
  if (s21_matrix_exists(A) || s21_matrix_exists(B)) {
    result_code = FAILURE;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
        result_code = FAILURE;
      }
    }
  }
  return result_code;
}

int s21_matrix_exists(matrix_t *result) {
  if (result == NULL || result->matrix == NULL || result->rows <= 0 ||
      result->columns <= 0) {
    return INCORRECT_MATRIX;
  }
  return OK;
}
