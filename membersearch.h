#ifndef MEMBERSEARCH_H
#define MEMBERSEARCH_H

#include "worker.h"
#include "adminmenu.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MemberSearch; }
QT_END_NAMESPACE

class MemberSearch : public QMainWindow
{
    Q_OBJECT

public:
    AdminMenu *parent;
    Worker *worker;

    explicit MemberSearch(AdminMenu *parent);
    ~MemberSearch();

private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_searchBar_returnPressed();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MemberSearch *ui;
};

#endif // MEMBERSEARCH_H
