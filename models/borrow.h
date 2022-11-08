#ifndef BORROW_H
#define BORROW_H

#include <QObject>
#include <QJsonObject>

class Borrow
{
    Q_GADGET

public:
    QString id, book_id, borrower_id;
    int issued_at, issued_for;

    void read(QJsonObject json)
    {
        id = json["id"].toString();
        book_id = json["book_id"].toString();
        borrower_id = json["borrower_id"].toString();
        issued_at = json["issued_at"].toInt();
        issued_for = json["issued_for"].toInt();
    }

    void write(QJsonObject json)
    {
        json["id"] = id;
        json["book_id"] = book_id;
        json["borrower_id"] = borrower_id;
        json["issued_at"] = issued_at;
        json["issued_for"] = issued_for;
    }
};

#endif // BORROW_H
