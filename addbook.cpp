#include "addbook.h"
#include "ui_addbook.h"

addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_buttonBox_accepted() // OK button - saves new book
{

}


void addBook::on_buttonBox_rejected()
{
    this->close();
}

