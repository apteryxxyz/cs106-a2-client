#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Login)
  , worker(new Worker(parent, ""))
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    delete worker;
}
