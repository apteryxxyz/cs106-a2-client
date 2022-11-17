#ifndef MANAGEAUTHOR_H
#define MANAGEAUTHOR_H

#include "worker.h"
#include "models/author.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ManageAuthor; }
QT_END_NAMESPACE

class ManageAuthor : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::ManageAuthor *ui;
    Author author;

    explicit ManageAuthor(Author author);
    ~ManageAuthor();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // MANAGEAUTHOR_H
