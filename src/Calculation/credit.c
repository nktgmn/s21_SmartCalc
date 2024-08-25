#include "credit.h"

void credit_annuity(int term, double sum, double rate, double *payment,
                    double *total_payment, double *overpayment) {
  if (fabs(rate) > 1e-6) {
    *payment = sum * rate / 100 / 12 / (1 - pow((1 + rate / 100 / 12), -term));
  } else {
    *payment = sum / term;
  }
  *total_payment = *payment * term;
  *overpayment = *total_payment - sum;
}

void credit_diff(int term, double sum, double rate, double *payments,
                 double *total_payment, double *overpayment) {
  *total_payment = 0;
  double diff_outstanding = sum;
  for (int i = 0; i < term; i++) {
    double diff_payment = sum / term + diff_outstanding * rate / 100 / 12;
    *total_payment = *total_payment + diff_payment;
    diff_outstanding = diff_outstanding - sum / term;
    payments[i] = diff_payment;
  }
  *overpayment = *total_payment - sum;
}