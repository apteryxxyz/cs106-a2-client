#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminmenu.h"
#include "ui_adminmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , worker(new Worker(parent, ""))
{
    ui->setupUi(this);
    AdminMenu *admin = new AdminMenu;  // Pops up admin menu. To be deleted with login function
    admin->show();
}

MainWindow::~MainWindow()
{

    delete ui;
    delete worker;
}
