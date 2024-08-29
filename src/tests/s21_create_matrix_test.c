#include "s21_tests.h"

START_TEST(s21_create_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix2) {
  int rows = 1919;
  int columns = 19;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix3) {
  int rows = 1;
  int columns = 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix4) {
  int rows = rand() % 100 + 1;
  int columns = 0;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix5) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix6) {
  int rows = -5;
  int columns = -5;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_1) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1000, 20000, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(create_matrix_2) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(create_matrix_3) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(create_matrix_4) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(6, 8, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(create_matrix_5) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1, 150, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(create_matrix_6) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(0, 0, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_matrix_7) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1, 0, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_matrix_8) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(0, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_matrix_9) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(-1, -1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_matrix_10) {
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, columns, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      m.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, columns);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_11) {
  const int rows = -1;
  const int columns = 2;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, columns, &m), 1);
}
END_TEST

START_TEST(create_matrix_12) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_13) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("create_matrix_tc");

  tcase_add_test(tc, create_matrix_1);
  tcase_add_test(tc, create_matrix_2);
  tcase_add_test(tc, create_matrix_3);
  tcase_add_test(tc, create_matrix_4);
  tcase_add_test(tc, create_matrix_5);
  tcase_add_test(tc, create_matrix_6);
  tcase_add_test(tc, create_matrix_7);
  tcase_add_test(tc, create_matrix_8);
  tcase_add_test(tc, create_matrix_9);
  tcase_add_test(tc, create_matrix_10);
  tcase_add_test(tc, create_matrix_11);
  tcase_add_test(tc, create_matrix_12);
  tcase_add_test(tc, create_matrix_13);

  tcase_add_test(tc, s21_create_matrix1);
  tcase_add_test(tc, s21_create_matrix2);
  tcase_add_test(tc, s21_create_matrix3);
  tcase_add_test(tc, s21_create_matrix4);
  tcase_add_test(tc, s21_create_matrix5);
  tcase_add_test(tc, s21_create_matrix6);

  suite_add_tcase(s, tc);
  return s;
}