#include "addauthor.h"
#include "ui_addauthor.h"

#include "models/author.h"
#include <QMessageBox>

AddAuthor::AddAuthor()
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::AddAuthor)
{
    ui->setupUi(this);
}

AddAuthor::~AddAuthor()
{
    delete ui;
    delete worker;
}

// Save new book
void AddAuthor::on_buttonBox_accepted()
{
    Author author;
    author.first_name = ui->line_first->text();
    author.last_name = ui->line_last->text();

    QJsonObject author_object;
    author.write(author_object);
    QJsonDocument author_document(author_object);
    QString author_response = worker->put("/authors", author_document.toJson());

    int author_error = worker->response_has_error(author_response);
    if (author_error > 0) {
        if (author_error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Author Created", "Author has successfully been created!");
    delete this;
}

void AddAuthor::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
