#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Login)
  , worker(new Worker(parent, ""))
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    delete worker;
}

void Login::on_LoginButton_clicked()
{
    // Create the credentials object
    QString email_address = ui->EmailInput->text();
    QString password = ui->PasswordInput->text();
    QJsonObject credentials;
    credentials.insert("email_address", email_address);
    credentials.insert("password", password);

    // Send the login request
    QJsonDocument login_body;
    login_body.setObject(credentials);
    QString login_response = worker->post("/login", login_body.toJson());
    QJsonDocument login_doc = QJsonDocument::fromJson(login_response.toUtf8());
    QJsonObject login_object = login_doc.object();

    if (login_response.contains("status")) {
        // If the login response has the "status" field, then an error ocurred
        QMessageBox::information(this, "Login Failed", "Incorrect email or password");
    } else {
        // QString token = login_object("token").toString();
        int type = login_object.value("user_type").toInt();

        if (type == 1) {
            // Successful admin login, show admin window
            QMessageBox::information(this, "Login Successful", "You are an admin!");
        } else if (type == 2) {
            // Successful member login, show member window
            QMessageBox::information(this, "login Successful", "You are a member!");
        } else {
            QMessageBox::information(this, "Unknown Error", "An unknown error has occurred!");
        }
    }
}

