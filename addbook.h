#ifndef ADDBOOK_H
#define ADDBOOK_H

#include "worker.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AddBook; }
QT_END_NAMESPACE

class AddBook : public QDialog
{
    Q_OBJECT

public:
    explicit AddBook();
    ~AddBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddBook *ui;
    Worker *worker;
};

#endif // ADDBOOK_H
