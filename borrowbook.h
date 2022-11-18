#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include "worker.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class BorrowBook; }
QT_END_NAMESPACE

class BorrowBook : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::BorrowBook *ui;

    explicit BorrowBook();
    ~BorrowBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
};

#endif // BORROWBOOK_H
