#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_code = OK;
  if (s21_matrix_exists(A)) {
    result_code = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    result_code = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) !=
                 INCORRECT_MATRIX &&
             (A->rows == 1)) {
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t square = {0};
        if (s21_create_matrix(A->rows - 1, A->columns - 1, &square) !=
            INCORRECT_MATRIX) {
          double determinant = 0;
          s21_square_matrix(i, j, A, &square);
          s21_determinant(&square, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&square);
        } else {
          result_code = INCORRECT_MATRIX;
          break;
        }
      }
    }
  }
  return result_code;
}