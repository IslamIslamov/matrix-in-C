#include "s21_tests.h"

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(3, 4, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, CALC_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_normal) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);
  if (code1 == OK && code2 == OK) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 0;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;

    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;

    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    int code = s21_calc_complements(&m, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);
    if (code1 == OK) s21_remove_matrix(&m);
    if (code2 == OK) s21_remove_matrix(&expected);
    if (code == OK) s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(complements_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(0, 10, &A);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(10, 9, &A);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double const A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double const result_nums[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  int count = 0;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A_nums[count];
      count++;
    }
  }
  count = 0;
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      C.matrix[i][j] = result_nums[count];
      count++;
    }
  }
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements1) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements2) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  int res = s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), CALC_ERROR);

  if (res == OK) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix = {0}, res_org = {0}, res_my = {0};
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_incorrect);
  tcase_add_test(tc, test_one_by_one);
  tcase_add_test(tc, complements_2);
  tcase_add_test(tc, complements_3);
  tcase_add_test(tc, complements_5);

  tcase_add_test(tc, s21_calc_complements1);
  tcase_add_test(tc, s21_calc_complements2);
  tcase_add_test(tc, test_s21_calc_complements);

  suite_add_tcase(s, tc);
  return s;
}