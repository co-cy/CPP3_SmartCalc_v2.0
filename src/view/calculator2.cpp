//
// Created by co_cy on 27.12.22.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_Calculator2.h" resolved

#include "calculator2.h"

#include <QMap>

#include "ui_calculator2.h"

namespace s21 {

Calculator2::Calculator2(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::Calculator2) {
  ui_->setupUi(this);

  connect(ui_->asin, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->sin, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->acos, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->cos, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->tan, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->atan, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->sqrt, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->pow, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->log, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->nat_log, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->number_0, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_1, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_2, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_3, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_4, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_5, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_6, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_7, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_8, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_9, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->number_x, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->clear, SIGNAL(clicked()), this, SLOT(ClearExpression()));
  connect(ui_->cancel, SIGNAL(clicked()), this, SLOT(CancelAction()));

  connect(ui_->open_bracket, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->close_bracket, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->sum, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->sub, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->div, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->mul, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->mod, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->exponent, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->calc_exp, SIGNAL(clicked()), this, SLOT(CalcExpression()));
  connect(ui_->draw_graph, SIGNAL(clicked()), this, SLOT(DrawGraph()));

  connect(ui_->point, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->negate, SIGNAL(clicked()), this, SLOT(Negate()));

  connect(ui_->pi, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->calc_credit, SIGNAL(clicked()), this, SLOT(CalcCredit()));
  connect(ui_->calc_deposit, SIGNAL(clicked()), this, SLOT(CalcDeposit()));
  connect(ui_->append_change, SIGNAL(clicked()), this, SLOT(AddedChange()));
  connect(ui_->pop_change, SIGNAL(clicked()), this, SLOT(PopChange()));

  ui_->customPlot->addGraph();

  // line color blue for first graph
  ui_->customPlot->graph(0)->setPen(QPen(Qt::red));
  ui_->customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
  ui_->customPlot->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ScatterShape::ssCircle, 5));

  ui_->customPlot->xAxis2->setVisible(true);
  ui_->customPlot->xAxis2->setTickLabels(false);
  ui_->customPlot->yAxis2->setVisible(true);
  ui_->customPlot->yAxis2->setTickLabels(false);

  // make left and bottom axes always transfer their ranges to right and top
  // axes:
  connect(ui_->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
          ui_->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui_->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
          ui_->customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // let the ranges scale themselves so graph 0 fits perfectly in the visible
  // area:
  ui_->customPlot->graph(0)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
  // graphs by clicking:
  ui_->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                   QCP::iSelectPlottables);

  ui_->customPlot->xAxis->setTickLengthIn(3);  // ?????????? ?????????? ???? ??????
  ui_->customPlot->xAxis->setTickLengthOut(5);  // ?????????? ?????????? ?????? ??????
  ui_->customPlot->yAxis->setTickLengthIn(3);  // ?????????? ?????????? ???? ??????
  ui_->customPlot->yAxis->setTickLengthOut(5);  // ?????????? ?????????? ?????? ??????
}

Calculator2::~Calculator2() { delete ui_; }

void Calculator2::PressButton() {
  static QMap<QString, QString> converter = {
      {ui_->pow->objectName(), "^"},
      {ui_->point->objectName(), "."},
      {ui_->pi->objectName(), "pi"},
  };

  auto *button = dynamic_cast<QPushButton *>(sender());
  auto find_result = converter.find(button->objectName());
  if (find_result != converter.end()) {
    exp_controller_.Add(find_result.value());
  } else {
    exp_controller_.Add(button->text());
  }
  UpdateExpressionText();
}

void Calculator2::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  QFont new_font = ui_->expression->font();
  QFontMetrics fm(new_font);

  size_t n = 0;
  size_t max_n = 1000;
  double min_k = 0.2;
  double max_k = min_k + 0.1;

  while (n < max_n &&
         ((double)fm.height() < min_k * (double)ui_->expression->height())) {
    if (new_font.pixelSize() == -1) {
      new_font.setPointSize(new_font.pointSize() + 1);
    } else {
      new_font.setPixelSize(new_font.pixelSize() + 1);
    }
    fm = QFontMetrics(new_font);
    ++n;
  }

  n = 0;
  while (n < max_n &&
         ((double)fm.height() > max_k * (double)ui_->expression->height())) {
    if (new_font.pixelSize() == -1) {
      new_font.setPointSize(new_font.pointSize() - 1);
    } else {
      new_font.setPixelSize(new_font.pixelSize() - 1);
    }
    fm = QFontMetrics(new_font);
    ++n;
  }

  ui_->expression->setFont(new_font);
}

void Calculator2::ClearExpression() {
  exp_controller_.Clear();
  UpdateExpressionText();
}
void Calculator2::CancelAction() {
  if (!is_result_) {
    exp_controller_.Cancel();
  }
  UpdateExpressionText();
}
void Calculator2::Negate() {
  exp_controller_.Negate();
  UpdateExpressionText();
}
void Calculator2::CalcExpression() {
  if (is_result_) {
    CancelAction();
  }

  is_result_ = true;
  try {
    double result = exp_controller_.Calc(ui_->value_x->value());
    ui_->expression->setText(ui_->expression->text() + " = " +
                             QString::number(result));
  } catch (std::exception &e) {
    ui_->expression->setStyleSheet("color: red;");
    ui_->expression->setText(e.what());
  }
}

void Calculator2::DrawGraph() {
  int n =
      (int)((ui_->max_x->value() - ui_->min_x->value()) / ui_->step_x->value());

  if (n < 0) n = 0;
  if (n > 500000) n = 500000;

  static QVector<double> x(500000);
  x.resize(0);

  for (int i = 0; i < n; ++i) {
    x.push_back(ui_->min_x->value() + ui_->step_x->value() * i);
  }

  try {
    ui_->customPlot->graph(0)->setData(x, exp_controller_.Calc(x));
    ui_->customPlot->replot();
  } catch (std::exception &e) {
    ui_->customPlot->graph(0)->data()->clear();
    ui_->customPlot->replot();
  }
}

void Calculator2::CalcCredit() {
  if (ui_->annuity->isChecked()) {
    double loan = ui_->loan_amount->value();
    int period = ui_->period->value();

    double res =
        Controller::CalcCreditAnnuity(loan, period, ui_->percent->value());
    double all = res * period;

    ui_->label_mon_pay->setText(QString::number(res));
    ui_->label_overpay->setText(QString::number(all - loan));
    ui_->label_all_pay->setText(QString::number(all));
  } else {
    double loan = ui_->loan_amount->value();
    int period = ui_->period->value();

    double start_res = Controller::CalcCreditDifferentiate(
        loan, period, 1, ui_->percent->value());
    double end_res = 0;
    if (period > 1)
      end_res = Controller::CalcCreditDifferentiate(loan, period, period,
                                                    ui_->percent->value());

    double all = start_res + end_res;
    for (int i = 2; i < period; i++)
      all += Controller::CalcCreditDifferentiate(loan, period, i,
                                                 ui_->percent->value());

    QString text = QString::number(start_res);
    if (period > 1) text += +" - " + QString::number(end_res);

    ui_->label_mon_pay->setText(text);
    ui_->label_overpay->setText(QString::number(all - loan));
    ui_->label_all_pay->setText(QString::number(all));
  }
}
void Calculator2::CalcDeposit() {
  static QMap<int, double> map_changed;
  map_changed.clear();
  double z = ui_->deposit_amount->value();

  bool ok = true;
  for (int i = 0; i < ui_->table_change->rowCount(); ++i) {
    int month = ui_->table_change->item(i, 0)->text().toInt(&ok);
    if (!ok) {
      break;
    }
    double amount = ui_->table_change->item(i, 1)->text().toDouble(&ok);
    if (!ok) {
      break;
    }
    if (month <= ui_->deposit_period->value()) {
      z += amount;
    }
    if (map_changed.find(month) != map_changed.end()) {
      map_changed[month] += amount;
    } else {
      map_changed[month] = amount;
    }
  }

  if (ok) {
    double deposit_amount = ui_->deposit_amount->value();
    int cur_index = ui_->pay_period->currentIndex();
    int pay_period;
    if (cur_index == 1) {
      pay_period = 3;
    } else if (cur_index == 2) {
      pay_period = 6;
    } else if (cur_index == 3) {
      pay_period = 12;
    } else {
      pay_period = 1;
    }

    try {
      auto res = Controller::CalcDeposit(
          deposit_amount, ui_->deposit_period->value(),
          ui_->deposit_percent->value(), ui_->deposit_tax_percent->value(),
          pay_period, ui_->capitalize->isChecked(), map_changed.cbegin(),
          map_changed.cend());
      ui_->label_finaly_percent->setText(QString::number(res.second - z));
      ui_->label_sum_tax->setText(QString::number(res.first));
      if (ui_->capitalize->isChecked()) {
        ui_->label_deposit_sum->setText(QString::number(res.second));
      } else {
        ui_->label_deposit_sum->setText(QString::number(z));
      }

    } catch (std::exception &e) {
      ui_->label_finaly_percent->setText(e.what());
      ui_->label_sum_tax->setText(e.what());
      ui_->label_deposit_sum->setText(e.what());
    }
    return;
  }

  ui_->label_finaly_percent->setText("????????????");
  ui_->label_sum_tax->setText("????????????");
  ui_->label_deposit_sum->setText("????????????");
}

void Calculator2::UpdateExpressionText() {
  if (is_result_) {
    is_result_ = false;
    ui_->expression->setStyleSheet("");
  }
  ui_->expression->setText(exp_controller_.String());
}

void Calculator2::AddedChange() {
  ui_->table_change->insertRow(ui_->table_change->rowCount());
  ui_->table_change->setItem(ui_->table_change->rowCount() - 1, 0,
                             new QTableWidgetItem("1"));
  ui_->table_change->setItem(ui_->table_change->rowCount() - 1, 1,
                             new QTableWidgetItem("100.0"));
}

void Calculator2::PopChange() {
  if (ui_->table_change->rowCount() > 0) {
    ui_->table_change->removeRow(ui_->table_change->rowCount() - 1);
  }
}
void Calculator2::keyPressEvent(QKeyEvent *event) {
  QWidget::keyPressEvent(event);
  if (ui_->tabWidget->currentIndex() != 0) {
    return;
  }

  if (event->key() == Qt::Key_0) {
    ui_->number_0->click();
  } else if (event->key() == Qt::Key_1) {
    ui_->number_1->click();
  } else if (event->key() == Qt::Key_2) {
    ui_->number_2->click();
  } else if (event->key() == Qt::Key_3) {
    ui_->number_3->click();
  } else if (event->key() == Qt::Key_4) {
    ui_->number_4->click();
  } else if (event->key() == Qt::Key_5) {
    ui_->number_5->click();
  } else if (event->key() == Qt::Key_6) {
    ui_->number_6->click();
  } else if (event->key() == Qt::Key_7) {
    ui_->number_7->click();
  } else if (event->key() == Qt::Key_8) {
    ui_->number_8->click();
  } else if (event->key() == Qt::Key_9) {
    ui_->number_9->click();
  } else if (event->key() == Qt::Key_X) {
    ui_->number_x->click();
  } else if (event->key() == Qt::Key_Backspace) {
    ui_->cancel->click();
  } else if (event->key() == Qt::Key_Return) {
    ui_->calc_exp->click();
  } else if (event->key() == Qt::Key_End) {
    ui_->clear->click();
  } else if (event->key() == Qt::Key_Plus) {
    ui_->sum->click();
  } else if (event->key() == Qt::Key_Minus) {
    ui_->sub->click();
  } else if (event->key() == Qt::Key_division) {
    ui_->div->click();
  } else if (event->key() == Qt::Key_multiply) {
    ui_->mul->click();
  } else if (event->key() == Qt::Key_AsciiCircum) {
    ui_->pow->click();
  } else if (event->key() == Qt::Key_Percent) {
    ui_->mod->click();
  } else if (event->key() == Qt::Key_Comma) {
    ui_->point->click();
  } else if (event->key() == Qt::Key_E) {
    ui_->exponent->click();
  } else if (event->key() == Qt::Key_S) {
    ui_->sin->click();
  } else if (event->key() == Qt::Key_C) {
    ui_->cos->click();
  } else if (event->key() == Qt::Key_T) {
    ui_->tan->click();
  } else if (event->key() == Qt::Key_P) {
    ui_->pi->click();
  } else if (event->key() == Qt::Key_ParenLeft) {
    ui_->open_bracket->click();
  } else if (event->key() == Qt::Key_ParenRight) {
    ui_->close_bracket->click();
  } else if (event->key() == Qt::Key_L) {
    ui_->log->click();
  }
}

}  // namespace s21