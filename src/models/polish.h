//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_MODELS_POLISH_H_
#define SMARTCALC_V2_0_SRC_MODELS_POLISH_H_

#include <QMap>
#include <QSet>
#include <QStack>
#include <QVector>

#include "lexeme.h"

namespace s21 {

class Polish {
  QStack<Lexeme> stack_;

 public:
  explicit Polish(QVector<Lexeme> lexemes);

  static int GetOperatorPriority(const QString &lexeme) noexcept {
    static const QMap<QString, int> kOperatorPriorities{
        {"(", 1},    {")", 1},   {"+", 2},    {"-", 2},    {"*", 3},
        {"/", 3},    {"mod", 3}, {"log", 3},  {"ln", 3},   {"sin", 3},
        {"cos", 3},  {"tan", 3}, {"asin", 3}, {"acos", 3}, {"atan", 3},
        {"sqrt", 3}, {"pi", 4},  {"x", 4},    {"^", 4}};
    auto it = kOperatorPriorities.find(lexeme);
    if (it == kOperatorPriorities.end()) {
      return 0;
    } else {
      return it.value();
    }
  }
  static int GetOperatorPriority(const Lexeme &lexeme) noexcept {
    return GetOperatorPriority(lexeme.string);
  }

  static bool IsOperator(const QString &lexeme) noexcept {
    static const QSet<QString> kOperators{"+", "-", "*", "/", "mod", "^"};
    return kOperators.find(lexeme) != kOperators.end();
  }
  static bool IsOperator(const Lexeme &lexeme) noexcept {
    return IsOperator(lexeme.string);
  }

  double Calc(long double x);
};
}  // namespace s21

#endif  // SMARTCALC_V2_0_SRC_MODELS_POLISH_H_
