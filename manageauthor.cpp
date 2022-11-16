#include "manageauthor.h"
#include "ui_manageauthor.h"

#include "models/author.h"
#include <QMessageBox>

ManageAuthor::ManageAuthor(Author author)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ManageAuthor)
{
    ui->setupUi(this);
    this->author = author;

    // Pre define input text values
    ui->line_first->setText(author.first_name);
    ui->line_last->setText(author.last_name);
}

ManageAuthor::~ManageAuthor()
{
    delete ui;
    delete worker;
}

// Save new book
void ManageAuthor::on_buttonBox_accepted()
{
    author.first_name = ui->line_first->text();
    author.last_name = ui->line_last->text();

    QJsonObject author_object;
    author.write(author_object);
    QJsonDocument author_document(author_object);

    QString response;
    // I 
    if (author.id == "") {
        QString created_author = worker->put("/authors", author_document.toJson());
        response = created_author;
    } else {
        std::string endpoint = "/authors/" + author.id.toStdString();
        QString updated_author = worker->post(endpoint, author_document.toJson());
        response = updated_author;
    }

    int author_error = worker->response_has_error(response);
    if (author_error > 0) {
        if (author_error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Author Updated", "Author has been successfully updated!");
    delete this;
}

void ManageAuthor::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
