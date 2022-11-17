#ifndef WORKER_H
#define WORKER_H

#include "models/user.h"

#include <string>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Worker : public QObject
{
    Q_OBJECT
    QNetworkAccessManager* manager;
    std::string base_url = "https://lms.apteryx.xyz/api";

public:
    QString token = "";
    User user;

    Worker();
    ~Worker();

public slots:
    void set_token(QString new_token);
    void set_config(Worker *old_worker);
    void set_config(QString new_token, User new_user);
    QString wait_for_reply(QNetworkReply*reply);
    int response_has_error(QString response);

    QString get(std::string location);
    QString post(std::string location, QByteArray data);
    QString put(std::string location, QByteArray data);
    // 'delete' is a c++ keyword, so use 'remove'
    QString remove(std::string location);
};

#endif // WORKER_H
