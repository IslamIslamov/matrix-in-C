#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int result_code = OK;

  if (A->rows != A->columns) return CALC_ERROR;
  if (s21_matrix_exists(A) != OK) return INCORRECT_MATRIX;

  double det = .0;
  if (s21_determinant(A, &det) != OK || det == 0) {
    result_code = CALC_ERROR;
  } else {
    matrix_t temp = {0};
    matrix_t temp2 = {0};
    result_code = s21_transpose(A, &temp);

    if (result_code == OK) {
      result_code = s21_calc_complements(&temp, &temp2);
    }
    if (result_code == OK) {
      result_code = s21_mult_number(&temp2, 1 / det, result);
    }
    if (result_code == OK) {
      s21_remove_matrix(&temp), s21_remove_matrix(&temp2);
    }
  }
  return result_code;
}