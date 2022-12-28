//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_
#define SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_

#include "models/expression.h"

class ExpressionController {
 private:
  Expression expression_;

 public:
  void Add(const QString &string) { expression_.Add(string); };
  void Clear() { expression_.Clear(); }
  void Cancel() { expression_.Cancel(); };
  void Negate() { expression_.Negate(); };
  void Calc(double x) { expression_.Calc(x); };
  [[nodiscard]] const QString &String() const noexcept {
    return expression_.String();
  };
};

#endif  // SMARTCALC_V2_0_SRC_CONTROLLERS_EXPRESSION_CONTROLLER_H_
