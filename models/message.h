#ifndef MESSAGE_H
#define MESSAGE_H

#include "models/user.h"

#include <QObject>
#include <QJsonObject>

class Message
{
    Q_GADGET

public:

    QString id, recipient_id, subject, content;
    bool for_admin;
    int read_at;

    User recipient;

    void read(QJsonObject &json)
    {
        id = json["id"].toString();
        recipient_id = json["recipient_id"].toString();
        subject = json["subject"].toString();
        content = json["content"].toString();
        for_admin = json["for_admin"].toBool();
        read_at = json["read_at"].toInt();

        QJsonObject raw_recipient = json["recipient"].toObject();
        recipient.read(raw_recipient);
    }

    void write(QJsonObject &json)
    {
        json["id"] = id;
        json["recipient_id"] = recipient_id;
        json["subject"] = subject;
        json["content"] = content;
        json["for_admin"] = for_admin;
        json["read_at"] = read_at;

        QJsonObject temp_recipient;
        recipient.write(temp_recipient);
        json["recipient"] = temp_recipient;
    }
};

#endif // MESSAGE_H
