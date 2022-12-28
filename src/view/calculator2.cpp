//
// Created by co_cy on 27.12.22.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_Calculator2.h" resolved

#include "calculator2.h"

#include <QLocale>
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

  connect(ui_->point, SIGNAL(clicked()), this, SLOT(PressButton()));
  connect(ui_->negate, SIGNAL(clicked()), this, SLOT(Negate()));

  connect(ui_->pi, SIGNAL(clicked()), this, SLOT(PressButton()));

  connect(ui_->calc_credit, SIGNAL(clicked()), this, SLOT(CalcCredit()));
  connect(ui_->calc_deposit, SIGNAL(clicked()), this, SLOT(CalcDeposit()));

  ui_->customPlot->addGraph();
  ui_->customPlot->graph(0)->setPen(
      QPen(Qt::red));  // line color blue for first graph
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

  ui_->customPlot->setBackground(
      ui_->graph_grid->palette().color(ui_->graph_grid->backgroundRole()));

  ui_->customPlot->xAxis->setBasePen(QPen(Qt ::white, 1));  // Перо оси
  ui_->customPlot->xAxis->setTickPen(QPen(Qt ::white, 1));  // Перо отметки оси
  ui_->customPlot->xAxis->setSubTickPen(
      QPen(Qt ::white, 1));  // Перо отметки оси
  ui_->customPlot->xAxis->setTickLabelColor(
      Qt ::white);  // цвет текста шкалы оси
  ui_->customPlot->xAxis->setLabelColor(Qt ::white);  // Цвет метки оси
  ui_->customPlot->xAxis->setTickLengthIn(3);  // Длина шкалы по оси
  ui_->customPlot->xAxis->setTickLengthOut(5);  // Длина шкалы вне оси

  ui_->customPlot->yAxis->setBasePen(QPen(Qt ::white, 1));  // Перо оси
  ui_->customPlot->yAxis->setTickPen(QPen(Qt ::white, 1));  // Перо отметки оси
  ui_->customPlot->yAxis->setSubTickPen(
      QPen(Qt ::white, 1));  // Перо отметки оси
  ui_->customPlot->yAxis->setTickLabelColor(
      Qt ::white);  // цвет текста шкалы оси
  ui_->customPlot->yAxis->setLabelColor(Qt ::white);  // Цвет метки оси
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
  exp_controller_.Cancel();
  UpdateExpressionText();
}
void Calculator2::Negate() {
  exp_controller_.Negate();
  UpdateExpressionText();
}
void Calculator2::CalcExpression() {
  ui_->expression->setText(QString::number(ui_->expression->text().toDouble()));
  QMessageBox::critical(nullptr, "ERROR", "NOT IMPL");
}
void Calculator2::CalcCredit() {
  QMessageBox::critical(nullptr, "ERROR", "NOT IMPL");
}
void Calculator2::CalcDeposit() {
  QMessageBox::critical(nullptr, "ERROR", "NOT IMPL");
}

void Calculator2::UpdateExpressionText() {
  ui_->expression->setText(exp_controller_.String());
}