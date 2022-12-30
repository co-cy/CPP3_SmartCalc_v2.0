//
// Created by co_cy on 29.12.22.
//

#include <gtest/gtest.h>

#include "controllers/controller.h"
using namespace s21;

TEST(CalcTest, sum) {
  Controller controller;

  controller.Add("1");
  controller.Add("+");
  controller.Add("1");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 2);
}

TEST(CalcTest, sub) {
  Controller controller;

  controller.Add("1");
  controller.Add("-");
  controller.Add("1");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0);
}

TEST(CalcTest, mul) {
  Controller controller;

  controller.Add("2.5");
  controller.Add("*");
  controller.Add("2");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 5);
}

TEST(CalcTest, div) {
  Controller controller;

  controller.Add("9.9");
  controller.Add("/");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 3.3);
}

TEST(CalcTest, mod1) {
  Controller controller;

  controller.Add("10");
  controller.Add("mod");
  controller.Add("2");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0);
}

TEST(CalcTest, mod2) {
  Controller controller;

  controller.Add("10");
  controller.Add("mod");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1);
}

TEST(CalcTest, pow) {
  Controller controller;

  controller.Add("2");
  controller.Add("^");
  controller.Add("3");
  controller.Add("^");
  controller.Add("2");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 512);
}

TEST(CalcTest, negate1) {
  Controller controller;

  controller.Add("2");
  controller.Negate();

  EXPECT_DOUBLE_EQ(controller.Calc(0), -2);
}

TEST(CalcTest, negate2) {
  Controller controller;

  controller.Add("2");
  controller.Negate();
  controller.Negate();

  EXPECT_DOUBLE_EQ(controller.Calc(0), 2);
}

TEST(CalcTest, negate3) {
  Controller controller;

  controller.Add("2");
  controller.Negate();
  controller.Negate();
  controller.Negate();
  controller.Negate();

  EXPECT_DOUBLE_EQ(controller.Calc(0), 2);
}

TEST(CalcTest, float_) {
  Controller controller;

  controller.Add("2.25");
  controller.Add("+");
  controller.Add("12.25");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 14.5);
}

TEST(CalcTest, exponent1) {
  Controller controller;

  controller.Add("1.25e3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1250);
}

TEST(CalcTest, exponent2) {
  Controller controller;

  controller.Add("1");
  controller.Add(".");
  controller.Add("2");
  controller.Add("5");
  controller.Add("e");
  controller.Add("+");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1250);
}

TEST(CalcTest, exponent3) {
  Controller controller;

  controller.Add("1");
  controller.Add(".");
  controller.Add("2");
  controller.Add("5");
  controller.Add("e");
  controller.Add("-");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0.00125);
}

TEST(CalcTest, cos) {
  Controller controller;

  controller.Add("cos");
  controller.Add("0");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1);
}

TEST(CalcTest, sin) {
  Controller controller;

  controller.Add("sin");
  controller.Add("pi");

  EXPECT_FALSE(controller.Calc(0) > 0.0000001);
}

TEST(CalcTest, tan) {
  Controller controller;

  controller.Add("tan");
  controller.Add("(");
  controller.Add("pi");
  controller.Add("/");
  controller.Add("4");
  controller.Add(")");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1);
}

TEST(CalcTest, acos) {
  Controller controller;

  controller.Add("acos");
  controller.Add("0");

  EXPECT_DOUBLE_EQ(controller.Calc(0), M_PI_2);
}

TEST(CalcTest, asin) {
  Controller controller;

  controller.Add("asin");
  controller.Add("1");

  EXPECT_DOUBLE_EQ(controller.Calc(0), M_PI_2);
}

TEST(CalcTest, atan) {
  Controller controller;

  controller.Add("atan");
  controller.Add("1");

  EXPECT_DOUBLE_EQ(controller.Calc(0), M_PI_4);
}

TEST(CalcTest, sqrt) {
  Controller controller;

  controller.Add("sqrt");
  controller.Add("81");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 9);
}

TEST(CalcTest, ln) {
  Controller controller;

  controller.Add("ln");
  controller.Add("1");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0);
}

TEST(CalcTest, log) {
  Controller controller;

  controller.Add("log");
  controller.Add("100");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 2);
}

TEST(CalcTest, cancel) {
  Controller controller;

  controller.Add("10");
  controller.Add("+");
  controller.Add("log");
  controller.Add("x");
  controller.Add("+");
  controller.Add("10");
  controller.Negate();
  controller.Add("10");

  controller.Cancel();
  controller.Cancel();
  controller.Cancel();
  controller.Cancel();
  controller.Cancel();
  controller.Cancel();
  controller.Cancel();
  controller.Cancel();

  EXPECT_DOUBLE_EQ(controller.Calc(0), 10);
}

TEST(CalcTest, bad1) {
  Controller controller;

  controller.Add("1");
  controller.Add(".");
  controller.Add(".");
  controller.Add("2");
  controller.Add("5");
  controller.Add("e");
  controller.Add("-");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0.00125);
}

TEST(CalcTest, bad2) {
  Controller controller;

  controller.Add("1");
  controller.Add(".");
  controller.Add("2");
  controller.Add("5");
  controller.Add("e");
  controller.Add("e");
  controller.Add("-");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0.00125);
}

TEST(CalcTest, bad3) {
  Controller controller;

  controller.Add("1");
  controller.Add(".");
  controller.Add("2");
  controller.Add("5");
  controller.Add("e");
  controller.Add("-");
  controller.Add("3");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 0.00125);
}

TEST(CalcTest, bad4) {
  Controller controller;

  controller.Add("1");
  controller.Add("a");

  EXPECT_DOUBLE_EQ(controller.Calc(0), 1);
}

TEST(CalcTest, bad5) {
  Controller controller;

  controller.Add("1");
  controller.Add("+");
  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, bad6) {
  Controller controller;

  controller.Add("+");
  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, bad7) {
  Controller controller;

  controller.Add("1");
  controller.Add("sin");
  controller.Add("0");

  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, bad8) {
  Controller controller;

  controller.Add("(");

  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, bad9) {
  Controller controller;

  controller.Add(")");

  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, bad10) {
  Controller controller;

  controller.Add("1");
  controller.Add("e");

  EXPECT_ANY_THROW(controller.Calc(0));
}

TEST(CalcTest, hard) {
  Controller controller;

  controller.Add("(");
  controller.Add("x");
  controller.Add("+");
  controller.Add("10");
  controller.Add("-");
  controller.Add("0");
  controller.Add("*");
  controller.Add("10");
  controller.Add("+");
  controller.Add("12");
  controller.Negate();
  controller.Add(")");

  EXPECT_DOUBLE_EQ(controller.Calc(100), 98);
}

TEST(CalcTest, creditA) {
  EXPECT_FALSE(Controller::CalcCreditAnnuity(1000, 1, 12) - 1009.999999 >
               0.001);
}

TEST(CalcTest, creditD) {
  EXPECT_DOUBLE_EQ(Controller::CalcCreditDifferentiate(1000, 1, 1, 12), 1010);
}

TEST(CalcTest, depositTest) {
  QMap<int, double> z{};
  auto r =
      s21::Controller::CalcDeposit(1000, 1, 12, 0, 1, 0, z.cbegin(), z.cend());

  EXPECT_DOUBLE_EQ(0, 0);
  EXPECT_DOUBLE_EQ(r.first, 0);
  EXPECT_DOUBLE_EQ(r.second, 1010);
}

TEST(CalcTest, depositTest2) {
  QMap<int, double> z{{1, 100}};
  auto r =
      s21::Controller::CalcDeposit(1000, 1, 12, 0, 1, 0, z.cbegin(), z.cend());

  EXPECT_DOUBLE_EQ(0, 0);
  EXPECT_DOUBLE_EQ(r.first, 0);
  EXPECT_DOUBLE_EQ(r.second, 1110);
}

TEST(CalcTest, depositTest3) {
  QMap<int, double> z{};
  auto r =
      s21::Controller::CalcDeposit(1000, 1, 12, 0, 1, 1, z.cbegin(), z.cend());

  EXPECT_DOUBLE_EQ(0, 0);
  EXPECT_DOUBLE_EQ(r.first, 0);
  EXPECT_DOUBLE_EQ(r.second, 1010);
}

TEST(CalcTest, depositTest4) {
  QMap<int, double> z{{1, -100000}};
  EXPECT_ANY_THROW(s21::Controller::CalcDeposit(1000, 1, 12, 0, 1, 1, z.cbegin(), z.cend()));
}
