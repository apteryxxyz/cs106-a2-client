#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AdminMenu; }
QT_END_NAMESPACE

class AdminMenu : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu(QWidget *parent = nullptr);
    ~AdminMenu();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_bookSearch_clicked();

    void on_pushButton_bookAdd_clicked();

    void on_pushButton_memberAdd_clicked();

    void on_pushButton_bookLog_clicked();

private:
    Ui::AdminMenu *ui;
};
#endif // ADMINMENU_H
