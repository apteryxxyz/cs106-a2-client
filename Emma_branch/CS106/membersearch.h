#ifndef MEMBERSEARCH_H
#define MEMBERSEARCH_H
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QDebug>


#include <QMainWindow>

namespace Ui {
class BookSearch;
}

class BookSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookSearch(QWidget *parent = nullptr);
    ~BookSearch();

private:
    Ui::BookSearch *ui;
};

#endif // MEMBERSEARCH_H
