#ifndef MEMBERMENU_H
#define MEMBERMENU_H

#include "worker.h"
#include "login.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MemberMenu; }
QT_END_NAMESPACE

class MemberMenu : public QMainWindow
{
    Q_OBJECT


public:
    Login *parent;
    Worker *worker;

    MemberMenu(Login *parent);
    ~MemberMenu();

    void show();

private slots:
    void on_pushButton_logout_clicked();
    void on_pushButton_bookSearch_clicked();
    void on_pushButton_memberInfo_clicked();
    void on_pushButton_messages_clicked();

    void on_pushButton_authorSearch_clicked();

private:
    Ui::MemberMenu *ui;
};
#endif // MEMBERMENU_H
