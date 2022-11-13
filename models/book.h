#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>

class Book
{
    Q_GADGET

public:
    QString id, isbn, author_id,
        title, description, genre, cover_image_url;
    int quantity;

    void read(QJsonObject &json)
    {
        id = json["id"].toString();
        isbn = json["isbn"].toString();
        author_id = json["author_id"].toString();
        title = json["title"].toString();
        description = json["description"].toString();
        genre = json["genre"].toString();
        cover_image_url = json["cover_image_url"].toString();
        quantity = json["quantity"].toInt();
    }

    void write(QJsonObject &json)
    {
        json["id"] = id;
        json["isbn"] = isbn;
        json["author_id"] = author_id;
        json["title"] = title;
        json["description"] = description;
        json["genre"] = genre;
        json["cover_image_url"] = cover_image_url;
        json["quantity"] = quantity;
    }
};

#endif // BOOK_H
