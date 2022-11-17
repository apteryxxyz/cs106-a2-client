#include "managebook.h"
#include "ui_managebook.h"

#include <QMessageBox>

ManageBook::ManageBook(Book book)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ManageBook)
{
    ui->setupUi(this);
    this->book = book;

    // Pre define input text values
    ui->line_isbn->setText(book.isbn);
    ui->line_title->setText(book.title);
    ui->line_description->setText(book.description);
    ui->line_author->setText(book.author.id);
    ui->line_cover->setText(book.cover_image_url);
    ui->line_genre->setText(book.genre);
    ui->line_quantity->setText(QString::number(book.quantity));

    if (book.id != "") {
        // Disable ISBN and author input
        ui->line_isbn->setEnabled(false);
        ui->line_author->setEnabled(false);
    }
}

ManageBook::~ManageBook()
{
    delete ui;
    delete worker;
}

// Save new book
void ManageBook::on_buttonBox_accepted()
{
    book.isbn = ui->line_isbn->text();
    book.title = ui->line_title->text();
    book.description = ui->line_description->text();
    book.author_id = ui->line_author->text();
    book.genre = ui->line_genre->text();
    book.cover_image_url = ui->line_cover->text();
    book.quantity = ui->line_quantity->text().toInt();

    QJsonObject book_object;
    book.write(book_object);
    QJsonDocument book_document(book_object);

    QString response;
    if (book.id == "") {
        QString created_book = worker->put("/books", book_document.toJson());
        response = created_book;
    } else {
        std::string endpoint = "/books/" + book.id.toStdString();
        QString updated_book = worker->post(endpoint, book_document.toJson());
        response = updated_book;
    }

    int book_error = worker->response_has_error(response);
    if (book_error > 0) {
        if (book_error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Book Updated", "Book has been successfully updated!");
    delete this;
}

void ManageBook::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
