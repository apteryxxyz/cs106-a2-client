#include "adminmenu.h"
#include "ui_adminmenu.h"

#include "booksearch.h"
#include "addbook.h"
#include "authorsearch.h"
#include "addauthor.h"

AdminMenu::AdminMenu(Login *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::AdminMenu)
{
    this->parent = parent;
    ui->setupUi(this);
}

AdminMenu::~AdminMenu()
{
    delete ui;
    delete worker;
}

void AdminMenu::on_pushButton_logout_clicked()
{
    this->hide();
    parent->show();
    delete this;
}

void AdminMenu::on_pushButton_authorAdd_clicked()
{
    // Show the add author pop up
    AddAuthor *author_add = new AddAuthor;
    author_add->worker->set_token(worker->token);
    author_add->show();
}


void AdminMenu::on_pushButton_authorSearch_clicked()
{
    // Show the author search screen, hide this
    AuthorSearch *author_search = new AuthorSearch(this);
    author_search->worker->set_token(worker->token);
    author_search->show();
    this->hide();
}

void AdminMenu::on_pushButton_bookSearch_clicked()
{
    // Show the book search screen, hide this
    BookSearch *book_search = new BookSearch(this);
    book_search->worker->set_token(worker->token);
    book_search->show();
    this->hide();
}

void AdminMenu::on_pushButton_bookAdd_clicked()
{
    // Show the add book pop up
    AddBook *book_add = new AddBook;
    book_add->worker->set_token(worker->token);
    book_add->show();
}

void AdminMenu::on_pushButton_memberAdd_clicked() {}

void AdminMenu::on_pushButton_bookLog_clicked() {}
