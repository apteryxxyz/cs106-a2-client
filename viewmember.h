#ifndef VIEWMEMBER_H
#define VIEWMEMBER_H

#include "worker.h"
#include "models/user.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ViewMember; }
QT_END_NAMESPACE

class ViewMember : public QDialog
{
    Q_OBJECT

public:
    Worker *worker;
    Ui::ViewMember *ui;
    User member;

    explicit ViewMember(User member);
    ~ViewMember();

private slots:
    void on_buttonBox_accepted();
};

#endif // VIEWMEMBER_H
