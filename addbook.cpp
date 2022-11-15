#include "addbook.h"
#include "ui_addbook.h"

// IDEA: This could probably be shared between "Add Book" and "Edit Book"

#include "models/book.h"
#include <QMessageBox>

AddBook::AddBook()
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
    delete worker;
}

// Save new book
void AddBook::on_buttonBox_accepted()
{
    // Ensure author exists within the database
    QString author_id = ui->line_author->text();
    std::string endpoint = "/authors/" + author_id.toStdString();
    QString author_response = worker->get(endpoint);

    int author_error = worker->response_has_error(author_response);
    if (author_error > 0) {
        QMessageBox::information(this, "Author Not Found", "Could not find an author with the ID " + author_id + ".");
        return;
    }

    Book book;
    book.isbn = ui->line_isbn->text();
    book.title = ui->line_title->text();
    book.description = ui->line_description->text();
    book.author_id = ui->line_author->text();
    book.genre = ui->combo_genre->currentText();
    book.cover_image_url = ui->line_cover->text();
    book.quantity = ui->line_quantity->text().toInt();

    QJsonObject book_object;
    book.write(book_object);
    QJsonDocument book_document(book_object);
    QString book_response = worker->put("/books", book_document.toJson());

    int book_error = worker->response_has_error(book_response);
    if (book_error > 0) {
        if (book_error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Book Created", "Book has successfully been created!");
    delete this;
}

void AddBook::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
