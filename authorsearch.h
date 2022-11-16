#ifndef AUTHORSEARCH_H
#define AUTHORSEARCH_H

#include "worker.h"
#include "adminmenu.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthorSearch; }
QT_END_NAMESPACE

class AuthorSearch : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu *parent;
    Worker *worker;

    explicit AuthorSearch(AdminMenu *parent);
    ~AuthorSearch();

private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::AuthorSearch *ui;
};

#endif // AUTHORSEARCH_H
