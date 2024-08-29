#include "s21_tests.h"

START_TEST(determinant1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant6) {
  const int size = 1;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -5, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant7) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  rows = -rows;
  s21_create_matrix(rows, rows, &m);
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant8) {
  matrix_t m = {0};
  int rows = 4;
  int cols = 5;
  s21_create_matrix(rows, cols, &m);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_determinant1) {
  int num = 3;
  matrix_t matrix = {0};
  double check = -51.7;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 6;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant3) {
  matrix_t matrix = {0};
  double check = 6.908;
  double result = 0;

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 0.56;
  matrix.matrix[0][1] = -4.5;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant5) {
  matrix_t matrix = {0};
  double result = 0;

  s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_determinant(&matrix, &result), CALC_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant6) {
  int num = 4;
  matrix_t matrix = {0};
  double check = 123;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 3;
  matrix.matrix[0][1] = 6;
  matrix.matrix[0][2] = 7;
  matrix.matrix[0][3] = 8;
  matrix.matrix[1][0] = -1;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 2;
  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 7;
  matrix.matrix[3][3] = 4;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant7) {
  int num = 4;
  matrix_t matrix = {0};
  double check = 128.1795;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = -3.576;
  matrix.matrix[0][1] = 67;
  matrix.matrix[1][0] = -1.9665;
  matrix.matrix[1][1] = 1;
  matrix.matrix[2][2] = 1;
  matrix.matrix[3][3] = 1;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant8) {
  int num = 4;
  matrix_t matrix = {0};
  double check = 979.613088;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 3.004;
  matrix.matrix[0][1] = 5.000201;
  matrix.matrix[0][2] = 7.00032;
  matrix.matrix[0][3] = 8;
  matrix.matrix[1][0] = -1;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 12;
  matrix.matrix[2][3] = 0;
  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 7.0014;
  matrix.matrix[3][3] = 4;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("determinant_tc");

  tcase_add_loop_test(tc, determinant1, 0, 100);
  tcase_add_loop_test(tc, determinant2, 0, 100);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_loop_test(tc, determinant7, 0, 100);
  tcase_add_test(tc, determinant8);

  tcase_add_test(tc, s21_determinant1);
  tcase_add_test(tc, s21_determinant3);
  tcase_add_test(tc, s21_determinant5);
  tcase_add_test(tc, s21_determinant6);
  tcase_add_test(tc, s21_determinant7);
  tcase_add_test(tc, s21_determinant8);

  suite_add_tcase(s, tc);
  return s;
}