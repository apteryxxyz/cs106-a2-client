#include "membermenu.h"
#include "ui_membermenu.h"

#include "booksearch.h"
#include "borrowsearch.h"
#include "borrowbook.h"
#include "returnbook.h"
#include "messagelog.h"
#include "viewmember.h"
#include "login.h"

MemberMenu::MemberMenu(Login *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::MemberMenu)
{
    this->parent = parent;
    ui->setupUi(this);
}

MemberMenu::~MemberMenu()
{
    delete ui;
    delete worker;
}

void MemberMenu::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
}

void MemberMenu::on_pushButton_logout_clicked()
{
    this->hide();
    parent->show();
    delete this;
}

void MemberMenu::on_pushButton_bookSearch_clicked()
{
    // Show the book search screen, hide this
    BookSearch *book_search = new BookSearch(this);
    book_search->worker->set_config(worker);
    book_search->setWindowState(Qt::WindowFullScreen);
    book_search->show();
    this->hide();
}

void MemberMenu::on_pushButton_memberInfo_clicked()
{
    ViewMember *popup = new ViewMember(worker->user);
    popup->show();
}

void MemberMenu::on_pushButton_messages_clicked()
{
    MessageLog *log = new MessageLog(this);
    log->worker->set_config(this->worker);
    log->setWindowState(Qt::WindowFullScreen);
    log->show();
    this->hide();
}

void MemberMenu::on_pushButton_authorSearch_clicked()
{
    BorrowSearch *search = new BorrowSearch(this);
    search->worker->set_config(this->worker);
    search->setWindowState(Qt::WindowFullScreen);
    search->show();
    this->hide();
}


void MemberMenu::on_pushButton_bookBorrow_clicked()
{
    BorrowBook *popup = new BorrowBook();
    popup->worker->set_config(this->worker);
    popup->show();
}


void MemberMenu::on_pushButton_bookReturn_clicked()
{
    ReturnBook *popup = new ReturnBook();
    popup->worker->set_config(this->worker);
    popup->show();
}

