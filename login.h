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
    Worker *worker;

    explicit Login();
    ~Login();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
