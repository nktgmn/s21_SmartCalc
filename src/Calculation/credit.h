#ifndef CREDIT_H
#define CREDIT_H

#include <math.h>
#include <stdlib.h>

enum credit_type { ANNUITY, DIFF };

void credit_annuity(int term, double sum, double rate, double *payment,
                    double *total_payment, double *overpayment);
void credit_diff(int term, double sum, double rate, double *payments,
                 double *total_payment, double *overpayment);

#endif  // CREDIT_H
