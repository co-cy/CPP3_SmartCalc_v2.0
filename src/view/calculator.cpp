void CalculatorWindow::calc_deposit() {
  double deposit_amount = this->ui->deposit_amount->value();
  int pay_period;
  int error_code = 0;

  int cur_index = this->ui->pay_period->currentIndex();
  if (cur_index == 0) {
    pay_period = 1;
  } else if (cur_index == 1) {
    pay_period = 3;
  } else if (cur_index == 2) {
    pay_period = 6;
    } else if (cur_index == 3) {
      pay_period = 12;
    } else {
      pay_period = 1;
    }

    char list_add[this->ui->list_add->text().size() + 1];
    memcpy(list_add, this->ui->list_add->text().toStdString().c_str(),
           this->ui->list_add->text().size());
    list_add[this->ui->list_add->text().size()] = 0;

    char list_remove[this->ui->list_remove->text().size() + 1];
    memcpy(list_remove, this->ui->list_remove->text().toStdString().c_str(),
           this->ui->list_remove->text().size());
    list_remove[this->ui->list_remove->text().size()] = 0;

    t_deposit a = deposit_calc(
        deposit_amount, this->ui->deposit_period->value(),
        this->ui->deposit_percent->value(),
        this->ui->deposit_tax_percent->value(), pay_period,
        this->ui->capitalize->isChecked(), list_add, list_remove, &error_code);
    if (error_code) {
      this->ui->label_finaly_percent->setText("Начисленные проценты: ОШИБКА");
      this->ui->label_sum_tax->setText("Сумма налога: ОШИБКА");
      this->ui->label_deposit_sum->setText(
          "Сумма на вкладе к концу срока: ОШИБКА");
    } else {
      this->ui->label_finaly_percent->setText(
          "Начисленные проценты: " +
          QString::number(a.contribution / deposit_amount * 100 - 100));
      this->ui->label_sum_tax->setText("Сумма налога: " +
                                       QString::number(a.tax));
      this->ui->label_deposit_sum->setText("Сумма на вкладе к концу срока: " +
                                           QString::number(a.contribution));
    }
  }
