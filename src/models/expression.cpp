//
// Created by co_cy on 28.12.22.
//

#include "expression.h"

#include "polish.h"

namespace s21 {

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
  } else if (Polish::GetOperatorPriority(string)) {
    if (lexeme_.size() == 0 || IsGoodLexeme()) {
      if (lexeme_.size() > 0) {
        lexemes_.push_back(Lexeme(lexeme_, lexeme_.toDouble()));
      }
      lexemes_.push_back(Lexeme(string));
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

void Expression::Cancel() {
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
      string_.chop(lexemes_.back().Size() + 1);
      lexemes_.pop_back();
    }
  }
}

void Expression::Negate() {
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

}  // namespace s21
