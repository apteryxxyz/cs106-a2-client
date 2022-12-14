#include "authorsearch.h"
#include "ui_authorsearch.h"

#include "models/author.h"
#include "manageauthor.h"
#include <QTableWidgetItem>

AuthorSearch::AuthorSearch(AdminMenu *parent)
    : QMainWindow()
    , worker(new Worker())
    , ui(new Ui::AuthorSearch)
{
    this->parent = parent;
    ui->setupUi(this);
}

AuthorSearch::~AuthorSearch()
{
    delete ui;
    delete worker;
}

void AuthorSearch::show()
{
    QMainWindow::show();

    QString name = worker->user.first_name;
    ui->label_welcome->setText("Welcome back, " + name);
    on_lineEdit_searchBar_returnPressed();
}

void AuthorSearch::on_pushButton_back_clicked()
{
    this->close();
    this->parent->show();
    delete this;
}

// A simple function to easily insert a row into the table
void add_item(Ui::AuthorSearch *ui, int row, int column, QString content) {
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if (column != 0)  item->setFlags(item->flags() ^ Qt::ItemIsEnabled);
    ui->tableWidget->setItem(row, column, item);
    //ui->tableWidget->resizeColumnsToContents();
    //Commented code allows for reactive resizing of columns but overrides default column width
}

void AuthorSearch::on_lineEdit_searchBar_returnPressed()
{
    QString query = ui->lineEdit_searchBar->text();

    std::string endpoint = "/authors?search=" + query.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonArray raw_authors = json.array();

    // Insert the book data into the table
    ui->tableWidget->setRowCount(raw_authors.size());
    for (int i = 0; i < raw_authors.size(); i++)
    {
        QJsonObject raw_author = raw_authors[i].toObject();
        Author author;
        author.read(raw_author);

        add_item(ui, i, 0, author.id);
        add_item(ui, i, 1, author.first_name);
        add_item(ui, i, 2, author.last_name);
    }
}

void AuthorSearch::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) return;

    // Get first item of row
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    QString id = item->text();

    // Get the existing author data
    std::string endpoint = "/authors/" + id.toStdString();
    QString response = worker->get(endpoint);

    int error = worker->response_has_error(response);
    if (error > 0) return; // This should never be reached

    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject raw_author = json.object();

    Author author;
    author.read(raw_author);

    // Open manage author window
    ManageAuthor *edit_author = new ManageAuthor(author);
    edit_author->worker->set_config(worker);

    edit_author->show();
}

