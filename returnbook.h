#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include "worker.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ReturnBook; }
QT_END_NAMESPACE

class ReturnBook : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::ReturnBook *ui;

    explicit ReturnBook();
    ~ReturnBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
};

#endif // RETURNBOOK_H
