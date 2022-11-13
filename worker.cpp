#include "worker.h"

Worker::Worker()
    : QObject()
{
    manager = new QNetworkAccessManager();
}

Worker::~Worker()
{
    delete manager;
}

void Worker::set_token(QString new_token)
{
    token = new_token;
}

// Shared wait for response method for all other methods
QString Worker::wait_for_reply(QNetworkReply*reply)
{
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return reply->readAll();
}

// Easy method of checking if a response has resulted in an error
// Returns 0 if no error, otherwise the HTTP status code
int Worker::response_has_error(QString response)
{
    QJsonDocument document = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject object = document.object();

    if (!object.contains("status")) return 0;
    return object.value("status").toInt();
}

QString Worker::get(std::string location)
{
    QNetworkRequest request(QUrl(QString::fromStdString(base_url + location)));
    request.setRawHeader("Authorization", token.toLocal8Bit());
    QNetworkReply* reply = manager->get(request);
    return wait_for_reply(reply);
}

QString Worker::post(std::string location, QByteArray data)
{
    QNetworkRequest request(QUrl(QString::fromStdString(base_url + location)));
    request.setRawHeader("Authorization", token.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->post(request, data);
    return wait_for_reply(reply);
}

QString Worker::put(std::string location, QByteArray data)
{
    QNetworkRequest request(QUrl(QString::fromStdString(base_url + location)));
    request.setRawHeader("Authorization", token.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->put(request, data);
    return wait_for_reply(reply);
}

QString Worker::remove(std::string location)
{
    QNetworkRequest request(QUrl(QString::fromStdString(base_url + location)));
    request.setRawHeader("Authorization", token.toLocal8Bit());
    QNetworkReply* reply = manager->deleteResource(request);
    return wait_for_reply(reply);
}
