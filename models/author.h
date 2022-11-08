#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include <QJsonObject>

class Author
{
    Q_GADGET

public:
    QString id, first_name, last_name;

    void read(QJsonObject json)
    {
        id = json["id"].toString();
        first_name = json["first_name"].toString();
        last_name = json["last_name"].toString();
    }

    void write(QJsonObject json)
    {
        json["id"] = id;
        json["first_name"] = first_name;
        json["last_name"] = last_name;
    }
};

#endif // AUTHOR_H
