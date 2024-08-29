#include "s21_tests.h"

START_TEST(s21_eq_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = 0;
      matrix2.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = rand_num;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix3) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = rand_num;
    }
  }
  matrix1.matrix[0][0] = 0;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix4) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = -rand_num;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix5) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  matrix1.matrix[0][0] = 1919191919;
  matrix2.matrix[0][0] = 1919191919;
  matrix1.matrix[1][1] = 0.11111111;
  matrix2.matrix[1][1] = 0.11111110;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix6) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(DBL_MIN, DBL_MAX);
      m.matrix[i][j] = rand_val;
      mtx.matrix[i][j] = rand_val;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(s21_eq_matrix8) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  s21_create_matrix(rows1, cols1, &mtx);
  ck_assert_int_eq(s21_eq_matrix(&m, &mtx), FAILURE);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(s21_eq_matrix9) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
}

START_TEST(s21_eq_matrix10) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix11) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix12) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 2;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix13) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix14) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix15) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.01;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1.01;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix16) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.01;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = -4;
  B.matrix[0][0] = 1.01;
  B.matrix[0][1] = -2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = -4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix17) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.00000000234;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_eq_matrix18) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0001;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("suite_eq_matrix");
  TCase *tc = tcase_create("eq_matrix_tc");

  tcase_add_test(tc, s21_eq_matrix1);
  tcase_add_test(tc, s21_eq_matrix2);
  tcase_add_test(tc, s21_eq_matrix3);
  tcase_add_test(tc, s21_eq_matrix4);
  tcase_add_test(tc, s21_eq_matrix5);
  tcase_add_test(tc, s21_eq_matrix6);
  tcase_add_test(tc, s21_eq_matrix8);
  tcase_add_test(tc, s21_eq_matrix9);
  tcase_add_test(tc, s21_eq_matrix10);
  tcase_add_test(tc, s21_eq_matrix11);
  tcase_add_test(tc, s21_eq_matrix12);
  tcase_add_test(tc, s21_eq_matrix13);
  tcase_add_test(tc, s21_eq_matrix14);
  tcase_add_test(tc, s21_eq_matrix15);
  tcase_add_test(tc, s21_eq_matrix16);
  tcase_add_test(tc, s21_eq_matrix17);
  tcase_add_test(tc, s21_eq_matrix18);

  suite_add_tcase(s, tc);
  return s;
}