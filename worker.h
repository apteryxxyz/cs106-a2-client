#ifndef WORKER_H
#define WORKER_H

#include <string>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

#include <QJsonDocument>
#include <QJsonObject>

class Worker : QObject
{
    Q_OBJECT
    QNetworkAccessManager* manager;
    std::string base_url = "https://lms.apteryx.xyz/api";

public:
    QString token = "";

    Worker();
    ~Worker();

public slots:
    void set_token(QString new_token);
    QString wait_for_reply(QNetworkReply*reply);
    int response_has_error(QString response);

    QString get(std::string location);
    QString post(std::string location, QByteArray data);
    QString put(std::string location, QByteArray data);
    // 'delete' is a c++ keyword, so use 'remove'
    QString remove(std::string location);
};

#endif // WORKER_H
