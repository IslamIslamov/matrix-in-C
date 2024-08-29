#include "s21_tests.h"

START_TEST(s21_mult_matrix1) {
  int rows = rand() % 100 + 1;
  int rows_columns = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(rows, rows_columns, &matrix1);
  s21_create_matrix(rows_columns, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_columns; j++)
      matrix1.matrix[i][j] = (double)rand() / 1919 + 0.1;
  }

  for (int i = 0; i < rows_columns; i++) {
    for (int j = 0; j < columns; j++)
      matrix2.matrix[i][j] = (double)rand() / 1919 + 0.1;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < rows_columns; k++) {
        check.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
      }
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix2) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(-1, 9, &matrix1);
  s21_create_matrix(9, -1, &matrix2);

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix3) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 9, &matrix1);
  s21_create_matrix(1, 9, &matrix2);

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), CALC_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(mult_matrix1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 10, &B);
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mult_matrix3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix4) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix5) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix6) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < mtx.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m.columns; k++)
        check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("mult_matrix_tc");

  tcase_add_test(tc, mult_matrix1);
  tcase_add_test(tc, mult_matrix3);
  tcase_add_test(tc, mult_matrix4);
  tcase_add_loop_test(tc, mult_matrix5, 0, 100);
  tcase_add_loop_test(tc, mult_matrix6, 0, 100);

  tcase_add_loop_test(tc, s21_mult_matrix1, 0, 100);
  tcase_add_test(tc, s21_mult_matrix2);
  tcase_add_test(tc, s21_mult_matrix3);
  suite_add_tcase(s, tc);
  return s;
}
