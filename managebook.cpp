#include "managebook.h"
#include "ui_managebook.h"

#include <QMessageBox>
#include <QPushButton>

ManageBook::ManageBook(Book book)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ManageBook)
{
    ui->setupUi(this);
    this->book = book;

    if (book.id == "") {
        // Creating new book
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create");
    } else {
        // Editing an existing book
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Save");
        auto delete_button = ui->buttonBox->button(QDialogButtonBox::Cancel);
        delete_button->setText("Delete");
        delete_button->setStyleSheet("background-color: red; color: white;");

        // Pre fill the input boxes
        ui->line_isbn->setText(book.isbn);
        ui->line_isbn->setEnabled(false);
        ui->line_title->setText(book.title);
        ui->line_description->setText(book.description);
        ui->line_author->setText(book.author.id);
        ui->line_author->setEnabled(false);
        ui->line_cover->setText(book.cover_image_url);
        ui->line_genre->setText(book.genre);
        ui->line_quantity->setText(QString::number(book.quantity));
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
    // Take the text from input boxes and set them to book
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
    // If book.id is empty, we are creating a new book
    if (book.id == "") {
        // Create new book
        QString created_book = worker->put("/books", book_document.toJson());
        response = created_book;
    } else {
        // Edit new book
        std::string endpoint = "/books/" + book.id.toStdString();
        QString updated_book = worker->post(endpoint, book_document.toJson());
        response = updated_book;
    }

    int error = worker->response_has_error(response);
    if (error > 0) {
        if (error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Book Saved", "Book has been successfully saved!");
    delete this;
}

void ManageBook::on_buttonBox_rejected()
{
    // If book.id exists, then this button is deleting the book
    if (book.id != "") {
        std::string endpoint = "/books/" + book.id.toStdString();
        QString response = worker->remove(endpoint);

        int error = worker->response_has_error(response);
        if (error > 0)
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        else
            QMessageBox::information(this, "Book Deleted", "Book has been successfully deleted!");
    }

    this->close();
    delete this;
}
