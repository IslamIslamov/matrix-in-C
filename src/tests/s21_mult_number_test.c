#include "s21_tests.h"

START_TEST(s21_mult_number1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(rows, columns, &check);

  double number = (double)rand() / 1919 + 0.1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(rows, columns, &check);

  double number = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number3) {
  double number = 19;
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(1, -9, &matrix);

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  rows = -rows;
  columns = -columns;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, columns, &check);
  double mult_number = get_rand(-10e5, 10e5);
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_mult_number_matrix(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("mult_number_tc");

  tcase_add_loop_test(tc, mult_number_1, 0, 50);
  tcase_add_loop_test(tc, mult_number_2, 0, 50);

  tcase_add_loop_test(tc, s21_mult_number1, 0, 50);
  tcase_add_loop_test(tc, s21_mult_number2, 0, 50);
  tcase_add_test(tc, s21_mult_number3);

  suite_add_tcase(s, tc);
  return s;
}