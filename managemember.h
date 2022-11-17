#ifndef MANAGEMEMBER_H
#define MANAGEMEMBER_H

#include "worker.h"
#include "models/user.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ManageMember; }
QT_END_NAMESPACE

class ManageMember : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::ManageMember *ui;
    User member;

    explicit ManageMember(User member);
    ~ManageMember();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // MANAGEMEMBER_H
