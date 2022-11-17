#include "adminmenu.h"
#include "ui_adminmenu.h"

#include "booksearch.h"
#include "managebook.h"
#include "authorsearch.h"
#include "manageauthor.h"

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
    Author author;
    ManageAuthor *author_add = new ManageAuthor(author);
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
    Book book;
    ManageBook *book_add = new ManageBook(book);
    book_add->worker->set_token(worker->token);
    book_add->show();
}

void AdminMenu::on_pushButton_memberAdd_clicked() {}

void AdminMenu::on_pushButton_bookLog_clicked() {}
