#include "booksearch.h"
#include "ui_booksearch.h"
#include "adminmenu.h"
#include "ui_adminmenu.h"

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

void BookSearch::on_pushButton_back_clicked() //Closes book search
{
    this->close();
    AdminMenu *admin = new AdminMenu;  // Doesn't need to be new. Just needs to reopen existing admin window which is currently hidden.
    admin->show();
}

