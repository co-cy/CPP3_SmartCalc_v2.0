//
// Created by co_cy on 27.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_VIEW_CALCULATOR2_H_
#define SMARTCALC_V2_0_SRC_VIEW_CALCULATOR2_H_

#include <QMainWindow>

#include "controllers/controller.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator2;
}
QT_END_NAMESPACE

namespace s21 {

class Calculator2 : public QMainWindow {
  Q_OBJECT

 public:
  explicit Calculator2(QWidget *parent = nullptr);
  ~Calculator2() override;

 protected:
  void resizeEvent(QResizeEvent *event) override;
  void UpdateExpressionText();
  bool is_result_ = false;
  void keyPressEvent(QKeyEvent *event) override;

 public slots:
  void PressButton();
  void ClearExpression();
  void CancelAction();
  void Negate();
  void CalcExpression();
  void CalcCredit();
  void CalcDeposit();
  void DrawGraph();

  void AddedChange();
  void PopChange();

 private:
  Ui::Calculator2 *ui_;
  Controller exp_controller_;
};

}  // namespace s21

#endif  // SMARTCALC_V2_0_SRC_VIEW_CALCULATOR2_H_
