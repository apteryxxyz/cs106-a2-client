#ifndef MESSAGELOG_H
#define MESSAGELOG_H

#include "worker.h"
#include "adminmenu.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MessageLog; }
QT_END_NAMESPACE

class MessageLog : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu *parent;
    Worker *worker;

    explicit MessageLog(AdminMenu *parent);
    ~MessageLog();

private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MessageLog *ui;
};

#endif // MESSAGELOG_H
