#include "borrowbook.h"
#include "ui_borrowbook.h"

#include "models/borrow.h"

#include <QMessageBox>
#include <QPushButton>

BorrowBook::BorrowBook()
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::BorrowBook)
{
    ui->setupUi(this);
}

BorrowBook::~BorrowBook()
{
    delete ui;
    delete worker;
}

// Save new book
void BorrowBook::on_buttonBox_accepted()
{
    // Take the text from input boxes and set them to borrow
    Borrow borrow;
    borrow.book_id = ui->line_book->text();
    QString time = ui->combo_for->currentText();
    int seconds = time == "3 Days" ? 259200 : time == "1 Week" ? 604800 : 604800 * 2;
    borrow.issued_for = seconds;

    QJsonObject borrow_object;
    borrow.write(borrow_object);
    QJsonDocument borrow_document(borrow_object);

    std::string endpoint = "/users/@me/borrows";
    QString response = worker->put(endpoint, borrow_document.toJson());

    int error = worker->response_has_error(response);
    if (error > 0) {
        if (error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you entered was invalid, please edit your inputs and try again.");
        else if (error == 409)
            QMessageBox::information(this, "Not Available", "This book is currently not available for borrow, try again later.");
        else
            QMessageBox::information(this, "Error", "Something went wrong, please try again.");
        return;
    }

    this->close();
    QMessageBox::information(this, "Book Borrowed", "Borrow has been successfully saved!");
    delete this;
}

void BorrowBook::on_buttonBox_rejected()
{
    this->close();
    delete this;
}
