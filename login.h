#ifndef LOGIN_H
#define LOGIN_H

#include "worker.h"

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::Login *ui;
    Worker *worker;
};

#endif // LOGIN_H
