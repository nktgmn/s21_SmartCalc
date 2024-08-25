#include "test.h"

START_TEST(OK_1) {
  const char *input = "-2 * sin(cos(-1 * 3.0 / 9 + 8))";
  double true_result = -2 * sin(cos(-1 * 3.0 / 9 + 8));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_2) {
  const char *input = "sin(cos(tan(atan(2 / 0.1 ^ 2))))";
  double true_result = sin(cos(tan(atan(2 / pow(0.1, 2)))));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_3) {
  const char *input = "54 mod 7 / 35 * (-2)";
  double true_result = 54 % 7 / 35.0 * (-2);

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_4) {
  const char *input = "3*acos(0)*6+8^3*1";
  double true_result = 3 * acos(0) * 6 + pow(8, 3) * 1;

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_5) {
  const char *input = "ln((sin(81^4)) ^2+(cos(3^16)) ^2)";
  double true_result =
      log(pow((sin(pow(81, 4))), 2) + pow((cos(pow(3, 16))), 2));
  ;

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_6) {
  const char *input = "sqrt((-1) ^ 2) / log(20)";
  double true_result = sqrt(pow(-1, 2)) / log10(20);

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_7) {
  const char *input = "-atan(tan(3))";
  double true_result = -atan(tan(3));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_8) {
  const char *input = "((sin(sin(sin(sin(999))))))";
  double true_result = ((sin(sin(sin(sin(999))))));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_9) {
  const char *input = "((sin(sin(sin(sin(999))))))";
  double true_result = ((sin(sin(sin(sin(999))))));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_10) {
  const char *input = "((sin(sin(sin(sin(999))))))";
  double true_result = ((sin(sin(sin(sin(999))))));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 1);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(OK_11) {
  const char *input = "((sin(sin(sin(sin(x))))))";
  double true_result = ((sin(sin(sin(sin(111))))));

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 1);
  swap_x(output, 111);
  double result = solve_postfix(output, &error);

  ck_assert_ldouble_eq_tol(true_result, result, S21_EPS);
  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_1) {
  const char *input = "((sin(sin(sin(sin(999))))))";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_2) {
  const char *input = "((((((((((2))))))))))";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_3) {
  const char *input = "((((((((((2)))))))))";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_4) {
  const char *input = "3..2 + 3";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_5) {
  const char *input = "0002 + 3";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_6) {
  const char *input = "7 - - 2";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_7) {
  const char *input = "7 * * 2";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_8) {
  const char *input = "sin(2)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, OK);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_9) {
  const char *input = "sin(x)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_10) {
  const char *input = "2 + !";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_11) {
  const char *input = "2 3";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_12) {
  const char *input = "2 + 3 - ";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_13) {
  const char *input = "00.01 + 2";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(SYNTAX_14) {
  const char *input = "7 + 3)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  ck_assert_int_eq(error, SYNTAX_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CALCULATION_1) {
  const char *input = "sqrt(-2)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, CALCULATION_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CALCULATION_2) {
  const char *input = "3 + ln(-1)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, CALCULATION_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CALCULATION_3) {
  const char *input = "3 + log(-1)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, CALCULATION_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CALCULATION_4) {
  const char *input = "asin(2)";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, CALCULATION_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CALCULATION_5) {
  const char *input = "1.0 / 0.0 - 1.0 / 0.0";

  Node *output = (Node *)malloc(sizeof(Node));
  create_node(output);

  int error = OK;
  infix_to_postfix(input, output, &error, 0);
  solve_postfix(output, &error);

  ck_assert_int_eq(error, CALCULATION_ERROR);

  free_node(output);
}
END_TEST

START_TEST(CREDIT_1) {
  int term = 12;
  double rate = 14;
  double sum = 100000;

  double payment, total_payment, overpayment;
  credit_annuity(term, sum, rate, &payment, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(payment, 8978.711761, S21_EPS);
  ck_assert_ldouble_eq_tol(total_payment, 107744.541134, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 7744.541134, S21_EPS);
}
END_TEST

START_TEST(CREDIT_2) {
  int term = 1;
  double rate = 14;
  double sum = 100000;

  double payment, total_payment, overpayment;
  credit_annuity(term, sum, rate, &payment, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(payment, 101166.666667, S21_EPS);
  ck_assert_ldouble_eq_tol(total_payment, 101166.666667, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 1166.666667, S21_EPS);
}
END_TEST

START_TEST(CREDIT_3) {
  int term = 600;
  double rate = 14;
  double sum = 100000;

  double payment, total_payment, overpayment;
  credit_annuity(term, sum, rate, &payment, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(payment, 1167.775573, S21_EPS);
  ck_assert_ldouble_eq_tol(total_payment, 700665.343965, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 600665.343965, S21_EPS);
}
END_TEST

START_TEST(CREDIT_4) {
  int term = 12;
  double rate = 14;
  double sum = 100000;

  double total_payment, overpayment;
  double *payments = malloc(term * sizeof(double));
  credit_diff(term, sum, rate, payments, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(total_payment, 107583.333333, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 7583.333333, S21_EPS);

  free(payments);
}
END_TEST

START_TEST(CREDIT_5) {
  int term = 1;
  double rate = 14;
  double sum = 100000;

  double total_payment, overpayment;
  double *payments = malloc(term * sizeof(double));
  credit_diff(term, sum, rate, payments, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(total_payment, 101166.666667, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 1166.666667, S21_EPS);

  free(payments);
}
END_TEST

START_TEST(CREDIT_6) {
  int term = 600;
  double rate = 14;
  double sum = 100000;

  double total_payment, overpayment;
  double *payments = (double *)malloc(term * sizeof(double));
  credit_diff(term, sum, rate, payments, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(total_payment, 450583.333333, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 350583.333333, S21_EPS);

  free(payments);
}
END_TEST

START_TEST(CREDIT_7) {
  int term = 10;
  double rate = 0;
  double sum = 100000;

  double payment, total_payment, overpayment;
  double *payments = (double *)malloc(term * sizeof(double));
  credit_annuity(term, sum, rate, &payment, &total_payment, &overpayment);

  ck_assert_ldouble_eq_tol(payment, 10000, S21_EPS);
  ck_assert_ldouble_eq_tol(total_payment, 100000, S21_EPS);
  ck_assert_ldouble_eq_tol(overpayment, 0, S21_EPS);

  free(payments);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  TCase *tc_ok;

  tc_ok = tcase_create("OK");
  suite_add_tcase(s, tc_ok);
  tcase_add_test(tc_ok, OK_1);
  tcase_add_test(tc_ok, OK_2);
  tcase_add_test(tc_ok, OK_3);
  tcase_add_test(tc_ok, OK_4);
  tcase_add_test(tc_ok, OK_5);
  tcase_add_test(tc_ok, OK_6);
  tcase_add_test(tc_ok, OK_7);
  tcase_add_test(tc_ok, OK_8);
  tcase_add_test(tc_ok, OK_9);
  tcase_add_test(tc_ok, OK_10);
  tcase_add_test(tc_ok, OK_11);

  TCase *tc_syntax;

  tc_syntax = tcase_create("SYNTAX");
  suite_add_tcase(s, tc_syntax);
  tcase_add_test(tc_syntax, SYNTAX_1);
  tcase_add_test(tc_syntax, SYNTAX_2);
  tcase_add_test(tc_syntax, SYNTAX_3);
  tcase_add_test(tc_syntax, SYNTAX_4);
  tcase_add_test(tc_syntax, SYNTAX_5);
  tcase_add_test(tc_syntax, SYNTAX_6);
  tcase_add_test(tc_syntax, SYNTAX_7);
  tcase_add_test(tc_syntax, SYNTAX_8);
  tcase_add_test(tc_syntax, SYNTAX_9);
  tcase_add_test(tc_syntax, SYNTAX_10);
  tcase_add_test(tc_syntax, SYNTAX_11);
  tcase_add_test(tc_syntax, SYNTAX_12);
  tcase_add_test(tc_syntax, SYNTAX_13);
  tcase_add_test(tc_syntax, SYNTAX_14);

  TCase *tc_calculation;

  tc_calculation = tcase_create("CALCULATION");
  suite_add_tcase(s, tc_calculation);
  tcase_add_test(tc_calculation, CALCULATION_1);
  tcase_add_test(tc_calculation, CALCULATION_2);
  tcase_add_test(tc_calculation, CALCULATION_3);
  tcase_add_test(tc_calculation, CALCULATION_4);
  tcase_add_test(tc_calculation, CALCULATION_5);

  TCase *tc_credit;

  tc_credit = tcase_create("CREDIT");
  suite_add_tcase(s, tc_credit);
  tcase_add_test(tc_credit, CREDIT_1);
  tcase_add_test(tc_credit, CREDIT_2);
  tcase_add_test(tc_credit, CREDIT_3);
  tcase_add_test(tc_credit, CREDIT_4);
  tcase_add_test(tc_credit, CREDIT_5);
  tcase_add_test(tc_credit, CREDIT_6);
  tcase_add_test(tc_credit, CREDIT_7);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  int nf = 0;

  s = lib_suite();
  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}