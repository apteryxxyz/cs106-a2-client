#include "booksearch.h"
#include "ui_booksearch.h"

#include "models/book.h"
#include <vector>

BookSearch::BookSearch(AdminMenu *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::BookSearch)
{
    ui->setupUi(this);
    this->parent = parent;
}

BookSearch::~BookSearch()
{
    delete ui;
    delete worker;
}

void BookSearch::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}

void BookSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();

    // TODO: Parse query into QUrlQuery
    std::string endpoint = "/books?q=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_books = json.array();

    // Insert the book data into the table
    ui->tableWidget->setRowCount(raw_books.size());
    for (int i = 0; i < raw_books.size(); i++) {
        QJsonObject raw_book = raw_books[i].toObject();
        Book book;
        book.read(raw_book);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(book.isbn));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(book.title));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(book.author_id));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(book.genre));
        // TODO: Quantity is not appearing in the table
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(book.quantity));
    }
}

