#include "s21_tests.h"

START_TEST(transpose_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  int tmp1, tmp2 = 0;
  tmp1 = s21_create_matrix(rows, cols, &m);

  matrix_t check = {0};
  tmp2 = s21_create_matrix(cols, rows, &check);

  if (tmp1 == OK && tmp2 == OK) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        double rand_val = get_rand(-10e10, 10e10);
        m.matrix[i][j] = rand_val;
        check.matrix[j][i] = rand_val;
      }
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  matrix_t check = {0};
  int tmp1 = s21_create_matrix(rows, cols, &m) == OK;
  int tmp2 = s21_create_matrix(cols, rows, &check) == OK;
  if (tmp1 == OK && tmp2 == OK) {
    matrix_t res = {0};
    ck_assert_int_eq(s21_transpose(&m, &res), INCORRECT_MATRIX);

    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

// START_TEST(transpose_matrix3) {
//   matrix_t A;
//   int res = s21_transpose(NULL, &A);
//   ck_assert_int_eq(res, 1);
// }
// END_TEST

START_TEST(transpose_matrix4) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(10, 10, &A);
  s21_remove_matrix(&A);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transpose_matrix5) {
  matrix_t A;
  matrix_t B;
  int tmp1 = s21_create_matrix(10, 10, &A);
  if (tmp1 == OK) {
    int res = s21_transpose(&A, &B);
    ck_assert_int_eq(res, 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}
END_TEST

START_TEST(s21_transpose1) {
  int num = rand() % 100 + 1;
  matrix_t matrix = {0};
  matrix_t check = {0};
  matrix_t result = {0};

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[j][i] = matrix.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix = {0};
  matrix_t check = {0};
  matrix_t result = {0};

  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(columns, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[j][i] = matrix.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose3) {
  int num = 3;
  matrix_t matrix = {0};
  matrix_t check = {0};
  matrix_t result = {0};

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 6;

  check.matrix[0][0] = 1;
  check.matrix[0][1] = 1;
  check.matrix[0][2] = 5;
  check.matrix[1][0] = 5;
  check.matrix[1][1] = 4.3;
  check.matrix[1][2] = 1;
  check.matrix[2][0] = 7;
  check.matrix[2][1] = 4;
  check.matrix[2][2] = 6;

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose4) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_transpose(&matrix, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("suite_transpose_matrix");
  TCase *tc = tcase_create("transpose_matrix_tc");

  tcase_add_loop_test(tc, transpose_matrix, 0, 100);
  tcase_add_loop_test(tc, transpose_matrix2, 0, 100);
  // tcase_add_test(tc, transpose_matrix3);
  tcase_add_test(tc, transpose_matrix4);
  tcase_add_test(tc, transpose_matrix5);

  tcase_add_loop_test(tc, s21_transpose1, 0, 100);
  tcase_add_loop_test(tc, s21_transpose2, 0, 100);
  tcase_add_test(tc, s21_transpose3);
  tcase_add_test(tc, s21_transpose4);

  suite_add_tcase(s, tc);
  return s;
}