#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include "worker.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AddAuthor; }
QT_END_NAMESPACE

class AddAuthor : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;

    explicit AddAuthor();
    ~AddAuthor();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddAuthor *ui;
};

#endif // ADDAUTHOR_H
