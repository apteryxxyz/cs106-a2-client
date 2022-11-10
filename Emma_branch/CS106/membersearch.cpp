#include "booksearch.h"
#include "ui_booksearch.h"

BookSearch::BookSearch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookSearch)
{
    ui->setupUi(this);
}

BookSearch::~BookSearch()
{
    delete ui;
}
