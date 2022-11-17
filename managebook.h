#ifndef MANAGEBOOK_H
#define MANAGEBOOK_H

#include "worker.h"
#include "models/book.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ManageBook; }
QT_END_NAMESPACE

class ManageBook : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::ManageBook *ui;
    Book book;

    explicit ManageBook(Book book);
    ~ManageBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
};

#endif // MANAGEBOOK_H
