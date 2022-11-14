#include "booksearch.h"
#include "ui_booksearch.h"

#include "models/book.h"
#include <QTableWidgetItem>

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

// A simple function to easily insert a row into the table
void add_item(Ui::BookSearch *ui, int row, int column, QString content) {
    QTableWidgetItem *item = new QTableWidgetItem(content);
    item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
}

void BookSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();
    // TODO: Parse query into QUrlQuery
    std::string endpoint = "/books?search=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_books = json.array();

    // Insert the book data into the table
    ui->tableWidget->setRowCount(raw_books.size());
    for (int i = 0; i < raw_books.size(); i++)
    {
        QJsonObject raw_book = raw_books[i].toObject();
        Book book;
        book.read(raw_book);

        add_item(ui, i, 0, book.isbn);
        add_item(ui, i, 1, book.title);
        add_item(ui, i, 2, book.author.first_name + " " + book.author.last_name);
        add_item(ui, i, 3, book.genre);
        // FIXME: Quantity is not appearing in the table
        add_item(ui, i, 4, QString::number(book.quantity));
    }
}
