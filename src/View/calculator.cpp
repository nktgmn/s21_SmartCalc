#include "calculator.h"

#include "../Calculation/credit.h"
#include "../Calculation/polish.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);

  QPushButton *symbolButtons[30];

  for (int i = 0; i < 30; i++) {
    QString symbolName;
    if (i < 29) {
      symbolName = "Button" + QString::number(i);
    } else {
      symbolName = "ButtonSpace";
    }
    symbolButtons[i] = Calculator::findChild<QPushButton *>(symbolName);
    connect(symbolButtons[i], SIGNAL(released()), this, SLOT(SymbolPressed()));
  }

  QPushButton *button_C = Calculator::findChild<QPushButton *>("ButtonC");
  QPushButton *button_AC = Calculator::findChild<QPushButton *>("ButtonAC");
  QPushButton *button_EQ = Calculator::findChild<QPushButton *>("ButtonEqual");
  QPushButton *button_GRAPH =
      Calculator::findChild<QPushButton *>("ButtonGraph");
  QPushButton *button_CREDIT =
      Calculator::findChild<QPushButton *>("ButtonCredit");
  connect(button_C, SIGNAL(released()), this, SLOT(ClearPressed()));
  connect(button_AC, SIGNAL(released()), this, SLOT(ClearPressed()));
  connect(button_EQ, SIGNAL(released()), this, SLOT(EqualPressed()));
  connect(button_GRAPH, SIGNAL(released()), this, SLOT(GraphPressed()));
  connect(button_CREDIT, SIGNAL(released()), this, SLOT(CreditPressed()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::SymbolPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  if (QString::compare(butVal, "space", Qt::CaseInsensitive) == 0) {
    butVal = " ";
  }
  QString displayVal = ui->Display->text();
  QString newVal = displayVal + butVal;

  int len = newVal.length();

  if (len <= 255) {
    ui->Display->setText(newVal);
  } else {
    ui->Solution->setText("SYMBOLS LIMIT EXCEEDED");
  }
}

void Calculator::ClearPressed() {
  ui->Solution->setText("");

  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();

  if (QString::compare(butVal, "AC") == 0) {
    ui->Display->setText("");
  } else {
    QString displayVal = ui->Display->text();
    int len = displayVal.length();
    if (len <= 1) {
      ui->Display->setText("");
    } else {
      QString newVal = displayVal.left(len - 1);
      ui->Display->setText(newVal);
    }
  }
}

void Calculator::EqualPressed() {
  QString input_display = ui->Display->text();

  Node *output = (Node *)malloc(sizeof(Node));

  create_node(output);

  std::string str = input_display.toStdString();
  const char *input = str.c_str();

  int error = OK;
  infix_to_postfix(input, output, &error, 0);

  if (error == OK) {
    double result = solve_postfix(output, &error);
    if (error == OK) {
      ui->Solution->setText(QString::number(result, 'g', 9));
    } else if (error == SYNTAX_ERROR) {
      ui->Solution->setText("SYNTAX ERROR");
    } else if (error == CALCULATION_ERROR) {
      ui->Solution->setText("CALCULATION ERROR");
    }
  } else {
    ui->Solution->setText("SYNTAX ERROR");
  }

  free_node(output);
}

int Calculator::GraphParams(double *x_min, double *x_max, double *y_min,
                            double *y_max, double *number_of_steps,
                            double *step) {
  int error = 0;

  QString x_min_str = ui->x_min->text();
  QString x_max_str = ui->x_max->text();
  QString y_min_str = ui->y_min->text();
  QString y_max_str = ui->y_max->text();
  QString number_of_steps_str = ui->steps->text();

  bool ok;

  *x_min = x_min_str.toDouble(&ok);
  if (!ok) {
    error = 1;
  }
  *x_max = x_max_str.toDouble(&ok);
  if (!ok) {
    error = 1;
  }
  *y_min = y_min_str.toDouble(&ok);
  if (!ok) {
    error = 1;
  }
  *y_max = y_max_str.toDouble(&ok);
  if (!ok) {
    error = 1;
  }
  *number_of_steps = number_of_steps_str.toDouble(&ok);
  if (!ok) {
    error = 1;
  }

  if ((*x_min >= *x_max) || (*y_min >= *y_max) || (*number_of_steps <= 0)) {
    error = 1;
  } else {
    *step = (*x_max - *x_min) / *number_of_steps;
  }

  return error;
}

void Calculator::GraphPressed() {
  QString input_display = ui->Display->text();
  std::string str = input_display.toStdString();
  const char *input = str.c_str();

  QChart *chart = new QChart();
  ui->graph->setChart(chart);
  chart->legend()->hide();

  QList<QLineSeries *> seriesList;
  QLineSeries *series = new QLineSeries();

  double x_min, x_max, y_min, y_max, number_of_steps, step;
  int chart_params =
      GraphParams(&x_min, &x_max, &y_min, &y_max, &number_of_steps, &step);

  for (int i = 0; (i < number_of_steps) && (chart_params == 0); i++) {
    Node *output = (Node *)malloc(sizeof(Node));
    create_node(output);

    int error = OK;
    infix_to_postfix(input, output, &error, 1);

    swap_x(output, x_min);

    double result = solve_postfix(output, &error);

    if ((result >= y_max) || (result <= y_min)) {
      if (series->points().isEmpty() == 0) {
        seriesList.append(series);
        series = new QLineSeries();
      }

    } else {
      series->append(x_min, result);
    }

    free_node(output);

    x_min += step;
  }

  seriesList.append(series);

  for (QLineSeries *s : seriesList) {
    QColor color(176, 149, 30);
    QPen pen(color);
    pen.setWidth(2);
    s->setPen(pen);

    chart->addSeries(s);
  }

  if (chart_params == 1) {
    ui->Solution->setText("GRAPH PARAMS ERROR");
  } else {
    ui->Solution->setText("");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(x_min, x_max);
    chart->axes(Qt::Vertical).back()->setRange(y_min, y_max);
    chart->setAnimationOptions(QChart::AllAnimations);
  }
}

void Calculator::CreditPressed() {
  int type = -1;
  double sum = -1;
  double rate = -1;
  int term = -1;

  int error = CalcParams(&term, &sum, &rate, &type);

  if (error == 0) {
    ui->Solution->setText("");
    if (type == ANNUITY) {
      double payment, total_payment, overpayment;
      credit_annuity(term, sum, rate, &payment, &total_payment, &overpayment);

      QString result = "Monthly payment: " + QString::number(payment, 'f', 2);
      result =
          result + "\nTotal payment: " + QString::number(total_payment, 'f', 2);
      result =
          result + "\nOverpayment: " + QString::number(overpayment, 'f', 2);

      ui->credit_result->setText(result);

    } else {
      double *payments = (double *)malloc(term * sizeof(double));
      double total_payment, overpayment;
      credit_diff(term, sum, rate, payments, &total_payment, &overpayment);

      QString result =
          "Total payment: " + QString::number(total_payment, 'f', 2);
      result =
          result + "\nOverpayment: " + QString::number(overpayment, 'f', 2);
      for (int i = 0; i < term; i++) {
        result = result + "\nMonth " + QString::number(i + 1) +
                 " payment: " + QString::number(payments[i], 'f', 2);
      }

      ui->credit_result->setText(result);

      free(payments);
    }

  } else {
    ui->credit_result->setText("");
    ui->Solution->setText("CALC PARAMS ERROR");
  }
}

int Calculator::CalcParams(int *term, double *sum, double *rate, int *type) {
  int error = 0;

  bool annu_is_checked = ui->radio_annu->isChecked();
  bool diff_is_checked = ui->radio_diff->isChecked();
  if (annu_is_checked) {
    *type = ANNUITY;
  } else if (diff_is_checked) {
    *type = DIFF;
  } else {
    error = 1;
  }

  QString term_str = ui->term->text();
  QString sum_str = ui->sum->text();
  QString rate_str = ui->rate->text();

  bool ok;
  *sum = sum_str.toDouble(&ok);
  if ((!ok) || (*sum <= 0)) {
    error = 1;
  }

  *rate = rate_str.toDouble(&ok);
  if ((!ok) || (*rate < 0)) {
    error = 1;
  }

  *term = term_str.toInt(&ok);
  if ((!ok) || (*term <= 0)) {
    error = 1;
  }

  return error;
}
