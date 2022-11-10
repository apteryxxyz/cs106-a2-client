#ifndef BOOKSEARCH_H
#define BOOKSEARCH_H
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

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::BookSearch *ui;
};

#endif // BOOKSEARCH_H
