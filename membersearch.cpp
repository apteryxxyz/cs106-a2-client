#include "membersearch.h"
#include "ui_membersearch.h"

#include "models/user.h"
#include "managemember.h"
#include <QTableWidgetItem>

MemberSearch::MemberSearch(AdminMenu *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::MemberSearch)
{
    ui->setupUi(this);
    this->parent = parent;
}

MemberSearch::~MemberSearch()
{
    delete ui;
    delete worker;
}

void MemberSearch::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
    on_lineEdit_searchBar_returnPressed();
}

void MemberSearch::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}

// A simple function to easily insert a row into the table
void add_item(Ui::MemberSearch *ui, int row, int column, QString content) {
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if (column != 0) item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
}

void MemberSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();
    std::string endpoint = "/users?members_only=1&search=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_members = json.array();

    // Insert the user data into the table
    ui->tableWidget->setRowCount(raw_members.size());
    for (int i = 0; i < raw_members.size(); i++)
    {
        QJsonObject raw_member = raw_members[i].toObject();
        User member;
        member.read(raw_member);

        add_item(ui, i, 0, member.id);
        add_item(ui, i, 1, member.first_name);
        add_item(ui, i, 2, member.last_name);
        add_item(ui, i, 3, member.email_address);
        add_item(ui, i, 4, member.phone_number);
    }
}

void MemberSearch::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) return;

    // Get first item of row
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    QString id = item->text();

    // Get the existing user data
    std::string endpoint = "/users/" + id.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject raw_member = json.object();

    User member;
    member.read(raw_member);

    // Open manage member window
    ManageMember *edit_member = new ManageMember(member);
    edit_member->worker->set_config(worker);

    edit_member->show();
}

