//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_
#define SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_

#include "models/expression.h"
#include "models/polish.h"

class ExpressionController {
 private:
  Expression expression_;

 public:
  void Add(const QString &string) { expression_.Add(string); };
  void Clear() { expression_.Clear(); }
  void Cancel() { expression_.Cancel(); };
  void Negate() { expression_.Negate(); };
  double Calc(long double x) {
    Polish polish{expression_.GetLexemes()};
    double result = polish.Calc(x);

    Clear();
    Add(QString::number(result));

    return result;
  };
  QVector<double> Calc(QVector<double> x) {
    Polish polish{expression_.GetLexemes()};

    QVector<double> y(x.size());
    for (int i = 0; i < x.size(); ++i) {
      y[i] = polish.Calc(x[i]);
    }

    return y;
  };
  [[nodiscard]] const QString &String() const noexcept {
    return expression_.String();
  };
};

#endif  // SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_
