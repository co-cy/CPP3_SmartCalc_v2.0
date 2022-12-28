//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_
#define SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_

#include <QLocale>
#include <QMap>
#include <QString>
#include <QVector>

class Expression {
 private:
  QString string_;
  QString lexeme_;
  QVector<QString> lexemes_;
  QVector<QString> polish_;

 public:
  Expression() {
    string_.reserve(256);
    lexeme_.reserve(16);
    lexemes_.reserve(32);
    polish_.reserve(32);
  };

  void Add(const QString &string);
  void Clear() {
    string_.clear();
    lexeme_.clear();
    lexemes_.clear();
  }
  void Cancel() {
    if (lexeme_.size() > 0) {
      lexeme_.chop(1);
      if (lexeme_.size() > 0) {
        string_.chop(1);
      } else {
        // remove char and space
        string_.chop(2);
      }

      // Removing the unary minus || plus
      if (lexeme_ == '-' || lexeme_ == '+') {
        lexeme_.chop(1);
        string_.chop(2);
      }
    } else {
      if (!lexemes_.empty()) {
        // remove lexeme and space
        string_.chop(lexemes_.back().size() + 1);
        lexemes_.pop_back();
      }
    }
  }
  void Negate() {
    if (lexeme_.size() > 0) {
      if (lexeme_[0] == '-') {
        lexeme_[0] = '+';
        string_[string_.size() - lexeme_.size()] = '+';
      } else if (lexeme_[0] == '+') {
        lexeme_[0] = '-';
        string_[string_.size() - lexeme_.size()] = '-';
      } else {
        string_.insert(string_.size() - lexeme_.size(), '-');
        lexeme_.insert(0, '-');
      }
    }
  }
  void Calc(double x);
  bool CalcPolish();
  [[nodiscard]] const QString &String() const noexcept { return string_; };

 protected:
  static int GetOperatorPriority(const QString &lexeme) noexcept {
    static const QMap<QString, int> operator_priorities{
        {"(", 1},    {")", 1},   {"+", 2},    {"-", 2},    {"*", 3},
        {"/", 3},    {"mod", 3}, {"log", 3},  {"ln", 3},   {"sin", 3},
        {"cos", 3},  {"tan", 3}, {"asin", 3}, {"acos", 3}, {"atan", 3},
        {"sqrt", 3}, {"pi", 4},  {"x", 4},    {"^", 4}};
    auto it = operator_priorities.find(lexeme);
    if (it == operator_priorities.end()) {
      return 0;
    } else {
      return it.value();
    }
  }
  bool IsGoodLexeme() {
    bool ok = false;
    lexeme_.toDouble(&ok);
    return ok;
  }
};

#endif  // SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_
