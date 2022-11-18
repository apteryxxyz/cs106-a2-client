#ifndef BOOKSEARCH_H
#define BOOKSEARCH_H

#include "worker.h"
#include "adminmenu.h"

#include <QMainWindow>
#include "membermenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BookSearch; }
QT_END_NAMESPACE

class BookSearch : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu *parent;
    MemberMenu *membermenu;
    Worker *worker;

    void show();
    
    explicit BookSearch(AdminMenu *parent);
   // BookSearch(MemberMenu *membermenu);
    ~BookSearch();



private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::BookSearch *ui;
};

#endif // BOOKSEARCH_H
