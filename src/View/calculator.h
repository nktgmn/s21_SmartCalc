#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <math.h>

#include <QMainWindow>
#include <QtCharts>

extern "C" {
#include "../Calculation/credit.h"
#include "../Calculation/polish.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private:
  Ui::Calculator *ui;

 private slots:
  void SymbolPressed();
  void ClearPressed();
  void EqualPressed();
  void GraphPressed();
  void CreditPressed();
  int GraphParams(double *x_min, double *x_max, double *y_min, double *y_max,
                  double *number_of_steps, double *step);
  int CalcParams(int *term, double *sum, double *rate, int *type);
};
#endif  // CALCULATOR_H
