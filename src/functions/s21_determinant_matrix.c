#include "../s21_matrix.h"

void s21_square_matrix(int rows, int columns, matrix_t *A, matrix_t *square) {
  int mini_rows = 0;
  int mini_columns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == rows) continue;
    mini_columns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns) continue;
      square->matrix[mini_rows][mini_columns] = A->matrix[i][j];
      mini_columns++;
    }
    mini_rows++;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int result_code = OK;
  if (s21_matrix_exists(A) || result == NULL) {
    result_code = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    result_code = CALC_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    *result = determinant_function(A);
  }
  return result_code;
}

double determinant_function(matrix_t *A) {
  double determinant = 0;
  if (A->rows == 1)
    determinant = A->matrix[0][0];
  else if (A->rows > 1) {
    matrix_t square = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &square);
    for (int sign = 1, i = 0; i < A->columns; i++, sign *= (-1)) {
      s21_square_matrix(0, i, A, &square);
      determinant += sign * A->matrix[0][i] * determinant_function(&square);
    }
    s21_remove_matrix(&square);
  }
  return determinant;
}