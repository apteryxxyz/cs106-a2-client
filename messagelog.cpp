#include "messagelog.h"
#include "ui_messagelog.h"

#include "models/message.h"
#include <QTableWidgetItem>
#include <QMessageBox>

MessageLog::MessageLog(QMainWindow *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::MessageLog)
{
    ui->setupUi(this);
    this->parent = parent;
}

MessageLog::~MessageLog()
{
    delete ui;
    delete worker;
}

void MessageLog::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
    on_lineEdit_searchBar_returnPressed();
}

void MessageLog::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}

// A simple function to easily insert a row into the table
void add_item(Ui::MessageLog *ui, int row, int column, QString content) {
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if (column != 0)  item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
    ui->tableWidget->resizeColumnsToContents();
}

void MessageLog::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();

    std::string endpoint = worker->user.type == User::Type::Admin
            ? "/messages?search=" + query.toStdString()
            : "/users/@me/messages?search=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_messages = json.array();

    // Insert the message data into the table
    ui->tableWidget->setRowCount(raw_messages.size());
    for (int i = 0; i < raw_messages.size(); i++)
    {
        QJsonObject raw_message = raw_messages[i].toObject();
        Message message;
        message.read(raw_message);

        add_item(ui, i, 0, message.id);
        add_item(ui, i, 1, message.subject);
    }
}

void MessageLog::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) return;

    // Get first item of row
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    QString id = item->text();

    // Get the existing message data
    std::string endpoint = worker->user.type == User::Type::Admin
            ? "/messages/" + id.toStdString()
            : "/users/@me/messages/" + id.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject raw_message = json.object();

    Message message;
    message.read(raw_message);

    QMessageBox::information(this, message.subject, message.content);
}

