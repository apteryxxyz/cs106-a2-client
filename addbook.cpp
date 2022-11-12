#include "addbook.h"
#include "ui_addbook.h"

// IDEA: This could probably be shared between "Add Book" and "Edit Book"

AddBook::AddBook()
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
    delete worker;
}

// Save new book
void AddBook::on_buttonBox_accepted() {}

void AddBook::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
