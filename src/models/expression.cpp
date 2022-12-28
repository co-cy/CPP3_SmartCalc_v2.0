//
// Created by co_cy on 28.12.22.
//

#include "expression.h"

void Expression::Add(const QString &string) {
  if (string == 'e') {
    if (!lexeme_.contains('e')) {
      lexeme_.push_back(string);
      string_.push_back(string);
    }
  } else if (string == '.') {
    if (!lexeme_.contains('.') && !lexeme_.contains('e')) {
      lexeme_.push_back(string);
      string_.push_back(string);
    }
  } else if ((string == '+' || string == '-') && lexeme_.size() > 0 &&
             lexeme_.back() == 'e') {
    lexeme_.push_back(string);
    string_.push_back(string);
  } else if (GetOperatorPriority(string)) {
    if (lexeme_.size() == 0 || IsGoodLexeme()) {
      if (lexeme_.size() > 0) {
        lexemes_.push_back(lexeme_);
      }
      lexemes_.push_back(string);
      if (string_.size() > 0) {
        string_.push_back(' ');
      }
      string_ += string;
      lexeme_.clear();
    }
  } else {
    lexeme_.push_back(string);

    if (IsGoodLexeme()) {
      if (lexeme_.size() == 1 && string_.size() > 0) {
        string_.push_back(' ');
      }
      string_.push_back(string);
    } else {
      lexeme_.chop(string.size());
    }
  }
}

bool Expression::CalcPolish() {
  if (!IsGoodLexeme()) {
    return false;
  } else if (lexeme_.size() != 0) {
    lexemes_.push_back(lexeme_);
    lexeme_.clear();
  }

  polish_.clear();
  for (const auto &lexeme : lexemes_) {
  }

  return true;
}
