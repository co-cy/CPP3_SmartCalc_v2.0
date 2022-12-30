//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_
#define SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_

#include <QString>
#include <QVector>

#include "lexeme.h"

namespace s21 {

class Expression {
 private:
  QString string_;
  QString lexeme_;
  QVector<Lexeme> lexemes_;

 public:
  Expression() {
    string_.reserve(256);
    lexeme_.reserve(16);
  };

  void Add(const QString &string);
  void Clear() {
    string_.clear();
    lexeme_.clear();
    lexemes_.clear();
  }
  void Cancel();
  void Negate();
  [[nodiscard]] const QString &String() const noexcept { return string_; };
  [[nodiscard]] const QVector<Lexeme> &GetLexemes() {
    if (lexeme_.size() > 0) {
      if (IsGoodLexeme()) {
        lexemes_.push_back(Lexeme(lexeme_, lexeme_.toDouble()));
        lexeme_.clear();
      } else {
        throw std::logic_error("Error");
      }
    }

    return lexemes_;
  }

 protected:
  [[nodiscard]] bool IsGoodLexeme() const noexcept {
    bool ok = false;
    lexeme_.toDouble(&ok);
    return ok;
  }
};

}  // namespace s21

#endif  // SMARTCALC_V2_0_SRC_MODELS_EXPRESSION_H_
