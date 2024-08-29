#include "s21_tests.h"

START_TEST(s21_sub_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t check = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = (double)rand() / 1919 + 0.1;
      matrix2.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t check = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = 0;
      matrix2.matrix[i][j] = 0;
      check.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix3) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 2, &matrix1);
  s21_create_matrix(3, 4, &matrix2);

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), CALC_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sub_matrix4) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(-1, 9, &matrix1);
  s21_create_matrix(1, -9, &matrix2);

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  s21_create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), CALC_ERROR);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_sub_matrix(void) {
  Suite *s = suite_create("suite_sub_matrix");
  TCase *tc = tcase_create("sub_matrix_tc");

  tcase_add_loop_test(tc, sub_matrix, 0, 100);
  tcase_add_loop_test(tc, sub_matrix1, 0, 100);
  tcase_add_loop_test(tc, sub_matrix2, 0, 100);

  tcase_add_loop_test(tc, s21_sub_matrix1, 0, 100);
  tcase_add_loop_test(tc, s21_sub_matrix2, 0, 100);
  tcase_add_test(tc, s21_sub_matrix3);
  tcase_add_test(tc, s21_sub_matrix4);

  suite_add_tcase(s, tc);
  return s;
}