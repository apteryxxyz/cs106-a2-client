#ifndef BORROW_H
#define BORROW_H

#include "models/book.h"
#include "models/user.h"

#include <QObject>
#include <QJsonObject>

class Borrow
{
    Q_GADGET

public:
    QString id, book_id, user_id;
    int issued_at, issued_for;

    Book book;
    User user;

    void read(QJsonObject &json)
    {
        id = json["id"].toString();
        book_id = json["book_id"].toString();
        user_id = json["user_id"].toString();
        issued_at = json["issued_at"].toInt();
        issued_for = json["issued_for"].toInt();

        book.read(json["book"].toObject());
        user.read(json["user"].toObject());
    }

    void write(QJsonObject &json)
    {
        json["id"] = id;
        json["book_id"] = book_id;
        json["user_id"] = user_id;
        json["issued_at"] = issued_at;
        json["issued_for"] = issued_for;

        json["book"] = QJsonObject();
        book.write(json["book"].toObject());
        json["user"] = QJsonObject();
        user.write(json["user"].toObject());
    }
};

#endif // BORROW_H
