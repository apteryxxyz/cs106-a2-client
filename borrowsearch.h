#ifndef BORROWSEARCH_H
#define BORROWSEARCH_H

#include "worker.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BorrowSearch; }
QT_END_NAMESPACE

class BorrowSearch : public QMainWindow
{
    Q_OBJECT

public:
    QMainWindow *parent;
    Worker *worker;

    void show();
    
    explicit BorrowSearch(QMainWindow *parent);
    ~BorrowSearch();

private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();

private:
    Ui::BorrowSearch *ui;
};

#endif // BORROWSEARCH_H
