//
// Created by co_cy on 28.12.22.
//

#ifndef SMARTCALC_V2_0_SRC_MODELS_LEXEME_H_
#define SMARTCALC_V2_0_SRC_MODELS_LEXEME_H_

#include <QString>
#include <utility>

struct Lexeme {
  QString string;
  bool is_num = false;
  long double number;

  Lexeme() : string(), is_num(false), number(0){};
  explicit Lexeme(QString str)
      : string(std::move(str)), is_num(false), number(0){};
  Lexeme(QString str, long double val)
      : string(std::move(str)), is_num(true), number(val){};
  [[nodiscard]] int Size() const noexcept { return string.size(); }

  [[nodiscard]] bool operator==(const QString &str) const noexcept {
    return string == str;
  }
  [[nodiscard]] bool operator==(const QChar &c) const noexcept {
    return string == c;
  }
  [[nodiscard]] bool operator!=(const QString &str) const noexcept {
    return string != str;
  }
  [[nodiscard]] bool operator!=(const QChar &c) const noexcept {
    return string != c;
  }
};

#endif  // SMARTCALC_V2_0_SRC_MODELS_LEXEME_H_
