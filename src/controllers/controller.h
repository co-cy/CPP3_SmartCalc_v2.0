//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_CONTROLLERS_CONTROLLER_H_
#define SMARTCALC_V2_0_SRC_CONTROLLERS_CONTROLLER_H_

#include <cmath>

#include "models/deposit.h"
#include "models/expression.h"
#include "models/polish.h"

namespace s21 {

class Controller {
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
  static double CalcCreditAnnuity(double loan_amount, int period,
                                  double percent) noexcept {
    percent = percent / 1200;  // convert % -> value (/ 100) and convert year
                               // percent -> month percent (/ 12)
    return (double)(loan_amount * percent * powl((1 + percent), period) /
                    (powl((1 + percent), period) - 1));
  }
  static double CalcCreditDifferentiate(double loan_amount, int period,
                                        int cur_period, double percent) {
    percent = percent / 1200;  // convert % -> value (/ 100) and convert year
                               // percent -> month percent (/ 12)

    return loan_amount / period +
           percent * (loan_amount - (loan_amount * (cur_period - 1) / period));
  }
  static QPair<double, double> CalcDeposit(
      double deposit_amount, int period, double percent, double tax_percent,
      int pay_period, int capitalize,
      QMap<int, double>::const_iterator begin_map,
      QMap<int, double>::const_iterator end_map) {
    return Deposit::CalcDeposit(deposit_amount, period, percent, tax_percent,
                                pay_period, capitalize, begin_map, end_map);
  }
};

}  // namespace s21

#endif  // SMARTCALC_V2_0_SRC_CONTROLLERS_CONTROLLER_H_
