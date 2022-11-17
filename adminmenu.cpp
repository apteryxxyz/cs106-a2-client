#include "adminmenu.h"
#include "ui_adminmenu.h"

#include "authorsearch.h"
#include "manageauthor.h"
#include "booksearch.h"
#include "managebook.h"
#include "membersearch.h"
#include "managemember.h"
#include "messagelog.h"

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

void AdminMenu::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
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
    author_add->worker->set_config(worker);
    author_add->show();
}

void AdminMenu::on_pushButton_authorSearch_clicked()
{
    // Show the author search screen, hide this
    AuthorSearch *author_search = new AuthorSearch(this);
    author_search->worker->set_config(worker);
    author_search->setWindowState(Qt::WindowFullScreen);
    author_search->show();
    this->hide();
}

void AdminMenu::on_pushButton_bookSearch_clicked()
{
    // Show the book search screen, hide this
    BookSearch *book_search = new BookSearch(this);
    book_search->worker->set_config(worker);
    book_search->setWindowState(Qt::WindowFullScreen);
    book_search->show();
    this->hide();
}

void AdminMenu::on_pushButton_bookAdd_clicked()
{
    // Show the add book pop up
    Book book;
    ManageBook *book_add = new ManageBook(book);
    book_add->worker->set_config(worker);
    book_add->show();
}

void AdminMenu::on_pushButton_memberSearch_clicked()
{
    // Show the member search screen, hide this
    MemberSearch *member_search = new MemberSearch(this);
    member_search->worker->set_config(worker);
    member_search->setWindowState(Qt::WindowFullScreen);
    member_search->show();
    this->hide();
}

void AdminMenu::on_pushButton_memberAdd_clicked()
{
    // Show the add member pop up
    User member;
    ManageMember *member_add = new ManageMember(member);
    member_add->worker->set_config(worker);
    member_add->show();
}

void AdminMenu::on_pushButton_bookLog_clicked()
{
    MessageLog *message_log = new MessageLog(this);
    message_log->worker->set_config(worker);
    message_log->setWindowState(Qt::WindowFullScreen);
    message_log->show();
    this->hide();
}
