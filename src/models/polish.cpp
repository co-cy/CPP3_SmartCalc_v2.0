//
// Created by co_cy on 28.12.22.
//

#include "polish.h"

#include <cmath>

Polish::Polish(QVector<Lexeme> lexemes) {
  QVector<Lexeme> operators{};

  for (; !lexemes.empty(); lexemes.pop_front()) {
    Lexeme& lexeme = lexemes.front();

    if (lexeme.is_num || lexeme == 'x' || lexeme == "pi") {
      stack_.push_back(std::move(lexeme));
    } else if (lexeme == ')') {
      while (!operators.empty() && operators.back() != '(') {
        stack_.push_back(std::move(operators.back()));
        operators.pop_back();
      }

      if (!operators.empty()) {
        operators.pop_back();

        while (!operators.empty() && !IsOperator(operators.back())) {
          stack_.push_back(std::move(operators.back()));
          operators.pop_back();
        }
      } else {
        throw std::logic_error("Not open brackets");
      }
    } else if (lexeme == '(' || !IsOperator(lexeme)) {
      operators.push_back(std::move(lexeme));
    } else {
      int cur_priority = GetOperatorPriority(lexeme);
      while (!operators.empty() &&
             cur_priority < GetOperatorPriority(operators.back())) {
        stack_.push_back(std::move(operators.back()));
        operators.pop_back();
      }
      operators.push_back(std::move(lexeme));
    }
  }

  while (!operators.empty()) {
    if (operators.back() == '(') {
        throw std::logic_error("Not close brackets");
    }
    stack_.push_back(std::move(operators.back()));
    operators.pop_back();
  }
}

double Polish::Calc(long double x) {
  QStack<long double> numbers{};

  for (const auto& kLexeme : stack_) {
    if (kLexeme.is_num) {
      numbers.push(kLexeme.number);
    } else if (kLexeme == 'x') {
      numbers.push(x);
    } else if (kLexeme == "pi") {
      numbers.push(M_PI);
    } else if (!numbers.empty()) {
      long double number_1 = numbers.pop();
      if (kLexeme == "cos") {
        numbers.push(cosl(number_1));
      } else if (kLexeme == "sin") {
        numbers.push(sinl(number_1));
      } else if (kLexeme == "tan") {
        numbers.push(tanl(number_1));
      } else if (kLexeme == "acos") {
        numbers.push(acosl(number_1));
      } else if (kLexeme == "asin") {
        numbers.push(asinl(number_1));
      } else if (kLexeme == "atan") {
        numbers.push(atanl(number_1));
      } else if (kLexeme == "sqrt") {
        numbers.push(sqrtl(number_1));
      } else if (kLexeme == "ln") {
        numbers.push(logl(number_1));
      } else if (kLexeme == "log") {
        numbers.push(log10l(number_1));
      } else if (!numbers.empty()) {
        long double number_2 = numbers.pop();
        if (kLexeme == '+') {
          numbers.push(number_2 + number_1);
        } else if (kLexeme == '-') {
          numbers.push(number_2 - number_1);
        } else if (kLexeme == '*') {
          numbers.push(number_2 * number_1);
        } else if (kLexeme == '/') {
          numbers.push(number_2 / number_1);
        } else if (kLexeme == '^') {
          numbers.push(powl(number_2, number_1));
        } else if (kLexeme == "mod") {
          numbers.push(fmodl(number_2, number_1));
        } else {
          throw std::logic_error("Unknown operation");
        }
      } else {
        throw std::logic_error("Few numbers");
      }
    } else {
      throw std::logic_error("Few numbers");
    }
  }

  if (numbers.size() != 1) {
    throw std::logic_error("Error");
  }

  return (double)numbers.pop();
}
