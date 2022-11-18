#include "booksearch.h"
#include "ui_booksearch.h"

#include "models/book.h"
#include "managebook.h"
#include <QTableWidgetItem>

BookSearch::BookSearch(QMainWindow *parent)
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

void BookSearch::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
    on_lineEdit_searchBar_returnPressed();
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
    if (column != 0) item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
}

void BookSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();
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

        add_item(ui, i, 0, book.id);
        add_item(ui, i, 1, book.isbn);
        add_item(ui, i, 2, book.title);
        add_item(ui, i, 3, book.author.first_name + " " + book.author.last_name);
        add_item(ui, i, 4, book.genre);
        add_item(ui, i, 5, QString::number(book.quantity));
    }
}

void BookSearch::on_tableWidget_cellClicked(int row, int column)
{
    if (User::Type::Admin == worker->user.type) //Checks user type before allowing editing of book info
    {
        if (column == 0) return;

        // Get first item of row
        QTableWidgetItem* item = ui->tableWidget->item(row, 0);
        QString id = item->text();

        // Get the existing author data
        std::string endpoint = "/books/" + id.toStdString();
        QString response = worker->get(endpoint);

        int error = worker->response_has_error(response);
        if (error > 0) return; // This should never be reached

        QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject raw_book = json.object();

        Book book;
        book.read(raw_book);

        // Open manage author window
        ManageBook* edit_book = new ManageBook(book);
        edit_book->worker->set_config(worker);

        edit_book->show();
    }
}




