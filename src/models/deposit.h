//
// Created by co_cy on 29.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_MODELS_DEPOSIT_H_
#define SMARTCALC_V2_0_SRC_MODELS_DEPOSIT_H_

#include <QMap>
#include <QPair>
#include <QString>

namespace s21 {
class Deposit {
 public:
  static QPair<double, double> CalcDeposit(
      double deposit_amount, int period, double percent, double tax_percent,
      int pay_period, int capitalize,
      QMap<int, double>::const_iterator begin_map,
      QMap<int, double>::const_iterator end_map) {
    tax_percent = tax_percent * pay_period / 1200;
    percent = percent * pay_period / 1200;

    double added = 0;
    QPair<double, double> result = {0, 0};
    for (int i = pay_period; i <= period; i += pay_period) {
      double tmp = deposit_amount * percent;
      result.first += tmp * (tax_percent);

      if (capitalize)
        deposit_amount += tmp * (1 - tax_percent);
      else
        added += tmp * (1 - tax_percent);

      while (begin_map != end_map && begin_map.key() <= i) {
        deposit_amount += begin_map.value();
        ++begin_map;
      }

      if (deposit_amount < 0) {
        throw std::logic_error("");
      }
    }

    result.second = deposit_amount;
    if (!capitalize) result.second += added;

    return result;
  }
};
}  // namespace s21

#endif  // SMARTCALC_V2_0_SRC_MODELS_DEPOSIT_H_
