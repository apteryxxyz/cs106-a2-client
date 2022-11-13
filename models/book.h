#ifndef BOOK_H
#define BOOK_H

#include "models/author.h"

#include <QObject>
#include <QJsonObject>

class Book
{
    Q_GADGET

public:
    QString id, isbn, author_id,
        title, description, genre, cover_image_url;
    int quantity;

    std::optional<Author> author;

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

        if (json.contains("author")) {
            QJsonObject raw = json["author"].toObject();
            Author new_author;
            new_author.read(raw);
            author = new_author;
        }
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
