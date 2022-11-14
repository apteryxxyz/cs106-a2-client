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

        QJsonObject raw_book = json["book"].toObject();
        book.read(raw_book);
        QJsonObject raw_user = json["user"].toObject();
        user.read(raw_user);
    }

    void write(QJsonObject &json)
    {
        json["id"] = id;
        json["book_id"] = book_id;
        json["user_id"] = user_id;
        json["issued_at"] = issued_at;
        json["issued_for"] = issued_for;

        QJsonObject temp_book;
        book.write(temp_book);
        json["book"] = temp_book;

        QJsonObject temp_user;
        user.write(temp_user);
        json["user"] = temp_user;
    }
};

#endif // BORROW_H
