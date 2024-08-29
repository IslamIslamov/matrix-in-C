#include "s21_tests.h"

START_TEST(s21_inverse_matrix1) {
  int num = 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 0.5;
  check.matrix[0][0] = 2;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), FAILURE);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix2) {
  int num = 2;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 3;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4;

  check.matrix[0][0] = 0.8;
  check.matrix[0][1] = -0.6;
  check.matrix[1][0] = -0.2;
  check.matrix[1][1] = 0.4;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix3) {
  int num = 4;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 6;
  matrix.matrix[0][1] = -5;
  matrix.matrix[0][2] = 8;
  matrix.matrix[0][3] = 4;
  matrix.matrix[1][0] = 9;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 5;
  matrix.matrix[1][3] = 2;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 7;
  matrix.matrix[3][0] = -4;
  matrix.matrix[3][1] = 8;
  matrix.matrix[3][2] = -8;
  matrix.matrix[3][3] = -3;

  check.matrix[0][0] = 5.56;
  check.matrix[0][1] = -0.77;
  check.matrix[0][2] = -0.93;
  check.matrix[0][3] = 4.73;
  check.matrix[1][0] = -3;
  check.matrix[1][1] = 0.5;
  check.matrix[1][2] = 0.5;
  check.matrix[1][3] = -2.5;
  check.matrix[2][0] = -5.36;
  check.matrix[2][1] = 0.87;
  check.matrix[2][2] = 0.83;
  check.matrix[2][3] = -4.63;
  check.matrix[3][0] = -1.12;
  check.matrix[3][1] = 0.04;
  check.matrix[3][2] = 0.36;
  check.matrix[3][3] = -0.96;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix4) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  int res = s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), INCORRECT_MATRIX);

  if (res == OK) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix5) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix6) {
  int num = 2;
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 1;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("inverse_matrix_tc");

  tcase_add_test(tc, s21_inverse_matrix1);
  tcase_add_test(tc, s21_inverse_matrix2);
  tcase_add_test(tc, s21_inverse_matrix3);
  tcase_add_test(tc, s21_inverse_matrix4);
  tcase_add_test(tc, s21_inverse_matrix5);
  tcase_add_test(tc, s21_inverse_matrix6);

  suite_add_tcase(s, tc);
  return s;
}