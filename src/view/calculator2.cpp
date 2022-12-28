//
// Created by co_cy on 27.12.22.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_Calculator2.h" resolved

#include "calculator2.h"

#include <QMap>

#include "ui_calculator2.h"

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

  ui_->customPlot->xAxis->setTickLengthIn(3);  // Длина шкалы по оси
  ui_->customPlot->xAxis->setTickLengthOut(5);  // Длина шкалы вне оси
  ui_->customPlot->yAxis->setTickLengthIn(3);  // Длина шкалы по оси
  ui_->customPlot->yAxis->setTickLengthOut(5);  // Длина шкалы вне оси
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

    ui_->label_mon_pay->setText("Ежемесячный платеж: " + QString::number(res));
    ui_->label_overpay->setText("Переплата по кредиту: " +
                                QString::number(all - loan));
    ui_->label_all_pay->setText("Общая выплата: " + QString::number(all));
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

    QString text = "Ежемесячный платеж: " + QString::number(start_res);
    if (period > 1) text += +" - " + QString::number(end_res);

    ui_->label_mon_pay->setText(text);
    ui_->label_overpay->setText("Переплата по кредиту: " +
                                QString::number(all - loan));
    ui_->label_all_pay->setText("Общая выплата: " + QString::number(all));
  }
}
void Calculator2::CalcDeposit() {
  QMessageBox::critical(nullptr, "ERROR", "NOT IMPL");
}

void Calculator2::UpdateExpressionText() {
  if (is_result_) {
    is_result_ = false;
    ui_->expression->setStyleSheet("");
  }
  ui_->expression->setText(exp_controller_.String());
}