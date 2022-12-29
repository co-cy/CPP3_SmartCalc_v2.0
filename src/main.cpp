//
// Created by co_cy on 23.12.22.
//

#include <QApplication>

#include "view/calculator2.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Calculator2 w;
  w.show();
  return QApplication::exec();
}
