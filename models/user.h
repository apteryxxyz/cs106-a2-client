#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonObject>

class User
{
    Q_GADGET

public:
    enum Type {
        Admin = 1,
        Member = 2,
    };
    Q_ENUM(Type)

    QString id;
    Type type;
    QString first_name, last_name,
        email_address, phone_number,
        home_address_1, home_address_2, post_code;

    void read(QJsonObject &json)
    {
        id = json["id"].toString();
        type = static_cast<Type>(json["type"].toDouble());
        first_name = json["first_name"].toString();
        last_name = json["last_name"].toString();
        email_address = json["email_address"].toString();
        phone_number = json["phone_number"].toString();
        home_address_1 = json["home_address_1"].toString();
        home_address_2 = json["home_address_2"].toString();
        post_code = json["post_code"].toString();
    }

    void write(QJsonObject &json)
    {
        json["id"] = id;
        json["type"] = type;
        json["first_name"] = first_name;
        json["last_name"] = last_name;
        json["email_address"] = email_address;
        json["phone_number"] = phone_number;
        json["home_address_1"] = home_address_1;
        json["home_address_2"] = home_address_2;
        json["post_code"] = post_code;
    }
};


#endif // USER_H
