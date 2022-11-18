#include "returnbook.h"
#include "ui_returnbook.h"

#include "models/borrow.h"

#include <QMessageBox>
#include <QPushButton>

ReturnBook::ReturnBook()
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
}

ReturnBook::~ReturnBook()
{
    delete ui;
    delete worker;
}

// Save new book
void ReturnBook::on_buttonBox_accepted()
{
    // Take the text from input boxes and set them to borrow

    QString borrow_id = ui->line_borrow->text();
    std::string endpoint = "/users/@me/borrows/" + borrow_id.toStdString();
    QString response = worker->remove(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) {
        if (error == 404)
            QMessageBox::information(this, "Invalid Data", "Could not find that borrow, ensure you are using the borrow ID and not the book ID.");
        else
            QMessageBox::information(this, "Error", "Something went wrong, please try again.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Book Returned", "Book has been successfully returned!");
    delete this;
}

void ReturnBook::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
