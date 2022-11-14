#ifndef BOOKSEARCH_H
#define BOOKSEARCH_H

#include "worker.h"
#include "adminmenu.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BookSearch; }
QT_END_NAMESPACE

class BookSearch : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu *parent;
    Worker *worker;

    explicit BookSearch(AdminMenu *parent);
    ~BookSearch();

private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();

private:
    Ui::BookSearch *ui;
};

#endif // BOOKSEARCH_H
