#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "booksearch.h"
#include "ui_booksearch.h"
#include "addbook.h"
#include "ui_addbook.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QDebug>


AdminMenu::AdminMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
}

AdminMenu::~AdminMenu()
{

    delete ui;
}


void AdminMenu::on_pushButton_logout_clicked()
{

}


void AdminMenu::on_pushButton_bookSearch_clicked()
{
            BookSearch *bk_search = new BookSearch;
            bk_search->show(); // opens BookSearch screen
            hide();  // hides AdminMenu
}

void AdminMenu::on_pushButton_bookAdd_clicked()
{
            addBook *bk_add = new addBook;
            bk_add->show(); // opens add Book pop up
}


void AdminMenu::on_pushButton_memberAdd_clicked()
{

}


void AdminMenu::on_pushButton_bookLog_clicked()
{

}

