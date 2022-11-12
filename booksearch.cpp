#include "booksearch.h"
#include "ui_booksearch.h"

BookSearch::BookSearch(AdminMenu *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::BookSearch)
{
    ui->setupUi(this);
    this->parent = parent;
}

BookSearch::~BookSearch()
{
    delete ui;
    delete worker;
}

void BookSearch::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}
