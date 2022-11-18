#include "viewmember.h"
#include "ui_viewmember.h"

#include <QMessageBox>
#include <QPushButton>

ViewMember::ViewMember(User member)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ViewMember)
{
    ui->setupUi(this);
    this->member = member;

    // Fill the input boxes
    ui->line_first->setText(member.first_name);
    ui->line_last->setText(member.last_name);
    ui->line_email->setText(member.email_address);
    ui->line_phone->setText(member.phone_number);
    ui->line_home_1->setText(member.home_address_1);
    ui->line_home_2->setText(member.home_address_2);
    ui->line_code->setText(member.post_code);
}

ViewMember::~ViewMember()
{
    delete ui;
    delete worker;
}

void ViewMember::on_buttonBox_accepted()
{
    this->close();
    delete this;
}
