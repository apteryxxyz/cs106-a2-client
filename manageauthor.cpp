#include "manageauthor.h"
#include "ui_manageauthor.h"

#include <QMessageBox>
#include <QPushButton>

ManageAuthor::ManageAuthor(Author author)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ManageAuthor)
{
    ui->setupUi(this);
    this->author = author;

    if (author.id == "") {
        // Creating new author
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create");
    } else {
        // Editing an existing author
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Save");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Delete");
        
        // Pre fill the input boxes
        ui->line_first->setText(author.first_name);
        ui->line_last->setText(author.last_name);
    }

}

ManageAuthor::~ManageAuthor()
{
    delete ui;
    delete worker;
}

// Save new book
void ManageAuthor::on_buttonBox_accepted()
{
    // Take the text from input boxes and set them to author
    author.first_name = ui->line_first->text();
    author.last_name = ui->line_last->text();

    QJsonObject author_object;
    author.write(author_object);
    QJsonDocument author_document(author_object);

    QString response;
    // If author.id is empty, we are creating a new author
    if (author.id == "") {
        QString created_author = worker->put("/authors", author_document.toJson());
        response = created_author;
    } else {
        std::string endpoint = "/authors/" + author.id.toStdString();
        QString updated_author = worker->post(endpoint, author_document.toJson());
        response = updated_author;
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
    QMessageBox::information(this, "Author Updated", "Author has been successfully updated!");
    delete this;
}

void ManageAuthor::on_buttonBox_rejected()
{
    // If author.id exists, then this button is deleting the author
    if (author.id != "") {
        std::string endpoint = "/authors/" + author.id.toStdString();
        QString response = worker->remove(endpoint);

        int error = worker->response_has_error(response);
        if (error > 0)
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        else
            QMessageBox::information(this, "Author Deleted", "Author has been successfully deleted!");
    }

    this->close();
    delete this;
}
