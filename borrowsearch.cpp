#include "borrowsearch.h"
#include "ui_borrowsearch.h"

#include "models/borrow.h"
#include <QTableWidgetItem>

BorrowSearch::BorrowSearch(QMainWindow *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::BorrowSearch)
{
    ui->setupUi(this);
    this->parent = parent;
}

BorrowSearch::~BorrowSearch()
{
    delete ui;
    delete worker;
}

void BorrowSearch::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
    on_lineEdit_searchBar_returnPressed();
}

void BorrowSearch::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}

// A simple function to easily insert a row into the table
void add_item(Ui::BorrowSearch *ui, int row, int column, QString content) {
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if (column != 0 && column != 1) item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
    //ui->tableWidget->resizeColumnsToContents();
    //Commented code allows for reactive resizing of columns but overrides default column width
}

void BorrowSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();
    std::string endpoint = "/users/@me/borrows?search=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_borrows = json.array();

    // Insert the book data into the table
    ui->tableWidget->setRowCount(raw_borrows.size());
    for (int i = 0; i < raw_borrows.size(); i++)
    {
        QJsonObject raw_borrow = raw_borrows[i].toObject();
        Borrow borrow;
        borrow.read(raw_borrow);

        add_item(ui, i, 0, borrow.id);
        add_item(ui, i, 1, borrow.book.id);
        add_item(ui, i, 2, borrow.book.title);
    }
}
