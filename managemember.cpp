#include "managemember.h"
#include "ui_managemember.h"

#include <QMessageBox>
#include <QPushButton>

ManageMember::ManageMember(User member)
    : QDialog()
    , worker(new Worker)
    , ui(new Ui::ManageMember)
{
    ui->setupUi(this);
    this->member = member;

    if (member.id == "") {
        // Creating new member
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create");
    } else {
        // Editing an existing member
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Save");
        auto delete_button = ui->buttonBox->button(QDialogButtonBox::Cancel);
        delete_button->setText("Delete");
        delete_button->setStyleSheet("background-color: red; color: white;");

        // Pre fill the input boxes
        ui->line_first->setText(member.first_name);
        ui->line_last->setText(member.last_name);
        ui->line_email->setText(member.email_address);
        ui->line_password->setEnabled(false);
        ui->line_phone->setText(member.phone_number);
        ui->line_home_1->setText(member.home_address_1);
        ui->line_home_2->setText(member.home_address_2);
        ui->line_code->setText(member.post_code);
    }
}

ManageMember::~ManageMember()
{
    delete ui;
    delete worker;
}

// Save new member
void ManageMember::on_buttonBox_accepted()
{
    // Take the text from input boxes and set them to member
    member.first_name = ui->line_first->text();
    member.last_name = ui->line_last->text();
    member.email_address = ui->line_email->text();
    member.phone_number = ui->line_phone->text();
    member.home_address_1 = ui->line_home_1->text();
    member.home_address_2 = ui->line_home_2->text();
    member.post_code = ui->line_code->text();
    member.type = User::Type::Member;

    QJsonObject member_object;
    member.write(member_object);
    if (member.id == "")
        member_object.insert("password", ui->line_password->text());
    QJsonDocument member_document(member_object);

    QString response;
    // If member.id is empty, we are creating a new member
    if (member.id == "") {
        // Create new member
        QString created_member = worker->put("/users", member_document.toJson());
        response = created_member;
    } else {
        // Edit new member
        std::string endpoint = "/users/" + member.id.toStdString();
        QString updated_member = worker->post(endpoint, member_document.toJson());
        response = updated_member;
    }

    int error = worker->response_has_error(response);
    if (error > 0) {
        if (error == 400)
            QMessageBox::information(this, "Invalid Data", "Something you enter was invalid, please edit your inputs and try again.");
        else if (error == 409)
            QMessageBox::information(this, "EDuplicate Data", "The email address you entered is already in use, please enter a different email address.");
        else
            QMessageBox::information(this, "Error", "Something went wrong, please try again.");
        return;
    }

    this->close();
    QMessageBox::information(this, "User Saved", "User has been successfully saved!");
    delete this;
}

void ManageMember::on_buttonBox_rejected()
{
    // If member.id exists, then this button is deleting the member
    if (member.id != "") {
        std::string endpoint = "/users/" + member.id.toStdString();
        QString response = worker->remove(endpoint);

        int error = worker->response_has_error(response);
        if (error > 0)
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred, please try again later.");
        else
            QMessageBox::information(this, "User Deleted", "User has been successfully deleted!");
    }

    this->close();
    delete this;
}
