#include "calculator.h"

#include "./ui_calculator.h"

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalculatorWindow) {
  ui->setupUi(this);

  void CalculatorWindow::pressing_button() {
    QPushButton *button = (QPushButton *)sender();

    if (this->isResult) this->cancel_action();

    QString text = this->ui->expression->text();
    QString newText = this->converter[button->objectName()];

    if (text.length()) {
      QChar lastSim = text[text.length() - 1];
      QChar curSim = newText[newText.length() - 1];

      if (((curSim == 'e') && this->lastString.indexOf("e") != -1) ||
          (curSim == 'e' && lastSim == '.') ||
          (curSim == '.' && lastSim == 'e') ||
          (newText.indexOf(".") != -1 && this->lastString.indexOf(".") != -1))
        return;

      if (((lastSim.isDigit() || lastSim == 'e' || lastSim == '.') &&
           curSim.isDigit()) ||
          (lastSim.isDigit() && (curSim == 'e' || curSim == '.'))) {
        this->ui->expression->setText(text + newText);
        this->lastString += newText;
      } else {
        this->ui->expression->setText(text + " " + newText);
        this->lastString = newText;
      }
    } else {
      this->ui->expression->setText(newText);
      this->lastString = newText;
    }
  }

  void CalculatorWindow::clear_expression() {
    this->isResult = false;
    this->lastString = "";
    this->ui->expression->setText(this->lastString);
  }

  void CalculatorWindow::cancel_action() {
    QString text = this->ui->expression->text();

    if (this->isResult) {
      this->isResult = false;

      text = this->lastString;

      this->ui->expression->setText(text);
    } else {
      int index = text.lastIndexOf(" ");
      if (index == -1) {
        clear_expression();
      } else {
        this->lastString = text.left(index);
        this->ui->expression->setText(this->lastString);
      }
    }
  }

  void CalculatorWindow::calc_expression() {
    QString text = this->ui->expression->text();

    if (!text.length()) return;

    if (this->isResult) text = this->lastString;
    this->isResult = true;

    if (text.indexOf("x") != -1) {
      int N = ui->max_x->value() - ui->min_x->value() / ui->step_x->value();
      if (N < 0) N = 0;

      if (N > 50000) N = 50000;

      QVector<double> x(N), y(N);
      for (int i = 0; i < N; ++i) {
        x[i] = ui->min_x->value() + ui->step_x->value() * i;

        long double result;
        char test2[text.size() + 1];
        memcpy(test2, text.toStdString().c_str(), text.size());
        test2[text.size()] = 0;

        int error_code = calc((char *)test2, x[i], &result);
        if (error_code) {
          this->lastString = text;
          this->ui->expression->setText(text + " = Ошибка");

          ui->customPlot->clearGraphs();
          ui->customPlot->replot();
          return;
        }
        y[i] = (double)result;
      }

      long double result;
      char test2[text.size() + 1];
      memcpy(test2, text.toStdString().c_str(), text.size());
      test2[text.size()] = 0;

      calc((char *)test2, this->ui->value_x->value(), &result);

      this->lastString = text;
      this->ui->expression->setText(text + " = " +
                                    QString::number((double)result));

      ui->customPlot->graph(0)->setData(x, y);
      ui->customPlot->replot();

      ui->tabWidget->setCurrentWidget(ui->graph_grid);
    } else {
      long double result;
      char test2[text.size() + 1];
      memcpy(test2, text.toStdString().c_str(), text.size());
      test2[text.size()] = 0;

      int error_code = calc((char *)test2, 0, &result);
      if (!error_code) {
        this->lastString = QString::number((double)result);
        this->ui->expression->setText(text + " = " + this->lastString);
      } else {
        this->lastString = text;
        this->ui->expression->setText(text + " = Ошибка");
      }
    }
  }

  void CalculatorWindow::negate() {
    QString text = this->ui->expression->text();

    if (!text.length()) return;

    if (this->isResult) {
      this->cancel_action();

      text = this->ui->expression->text();
    }

    int index = text.lastIndexOf(" ");
    if (text[index + 1] == '-')
      text[index + 1] = '+';
    else if (text[index + 1] == '+')
      text[index + 1] = '-';
    else
      text.insert(index + 1, '-');

    this->ui->expression->setText(text);
  }

  void CalculatorWindow::calc_credit() {
    if (this->ui->annuity->isChecked()) {
      double loan = this->ui->loan_amount->value();
      int period = this->ui->period->value();

      double res =
          credit_calc_annuity(loan, period, this->ui->percent->value());
      double all = res * period;

      this->ui->label_mon_pay->setText("Ежемесячный платеж: " +
                                       QString::number(res));
      this->ui->label_overpay->setText("Переплата по кредиту: " +
                                       QString::number(all - loan));
      this->ui->label_all_pay->setText("Общая выплата: " +
                                       QString::number(all));
    } else {
      double loan = this->ui->loan_amount->value();
      int period = this->ui->period->value();

      double start_res = credit_calc_differentiate(loan, period, 1,
                                                   this->ui->percent->value());
      double end_res = 0;
      if (period > 1)
        end_res = credit_calc_differentiate(loan, period, period,
                                            this->ui->percent->value());

      double all = start_res + end_res;
      for (int i = 2; i < period; i++)
        all += credit_calc_differentiate(loan, period, i,
                                         this->ui->percent->value());

      QString text = "Ежемесячный платеж: " + QString::number(start_res);
      if (period > 1) text += +" - " + QString::number(end_res);

      this->ui->label_mon_pay->setText(text);
      this->ui->label_overpay->setText("Переплата по кредиту: " +
                                       QString::number(all - loan));
      this->ui->label_all_pay->setText("Общая выплата: " +
                                       QString::number(all));
    }
  }

  void CalculatorWindow::calc_deposit() {
    double deposit_amount = this->ui->deposit_amount->value();
    int pay_period;
    int error_code = 0;

    int cur_index = this->ui->pay_period->currentIndex();
    if (cur_index == 0) {
      pay_period = 1;
    } else if (cur_index == 1) {
      pay_period = 3;
    } else if (cur_index == 2) {
      pay_period = 6;
    } else if (cur_index == 3) {
      pay_period = 12;
    } else {
      pay_period = 1;
    }

    char list_add[this->ui->list_add->text().size() + 1];
    memcpy(list_add, this->ui->list_add->text().toStdString().c_str(),
           this->ui->list_add->text().size());
    list_add[this->ui->list_add->text().size()] = 0;

    char list_remove[this->ui->list_remove->text().size() + 1];
    memcpy(list_remove, this->ui->list_remove->text().toStdString().c_str(),
           this->ui->list_remove->text().size());
    list_remove[this->ui->list_remove->text().size()] = 0;

    t_deposit a = deposit_calc(
        deposit_amount, this->ui->deposit_period->value(),
        this->ui->deposit_percent->value(),
        this->ui->deposit_tax_percent->value(), pay_period,
        this->ui->capitalize->isChecked(), list_add, list_remove, &error_code);
    if (error_code) {
      this->ui->label_finaly_percent->setText("Начисленные проценты: ОШИБКА");
      this->ui->label_sum_tax->setText("Сумма налога: ОШИБКА");
      this->ui->label_deposit_sum->setText(
          "Сумма на вкладе к концу срока: ОШИБКА");
    } else {
      this->ui->label_finaly_percent->setText(
          "Начисленные проценты: " +
          QString::number(a.contribution / deposit_amount * 100 - 100));
      this->ui->label_sum_tax->setText("Сумма налога: " +
                                       QString::number(a.tax));
      this->ui->label_deposit_sum->setText("Сумма на вкладе к концу срока: " +
                                           QString::number(a.contribution));
    }
  }
