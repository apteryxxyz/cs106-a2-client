#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , worker(new Worker(parent, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6ImFkbWluIiwiaWF0IjoxNjY3NTQxNDkxLCJleHAiOjE2Njc1NDUwOTF9.scpEBVRsrXdu4NcrFx-qTQCHgPhx9fFgbT27uXVPkeY"))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete worker;
}
