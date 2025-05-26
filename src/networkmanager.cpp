#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include "logger.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkManager::replyFinished);
}

void NetworkManager::sendRequest(const QString &url) {
    if (url.isEmpty()) return;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager->get(request);
    Logger::info(QString("Sending request to %1").arg(url).toStdString());
}

void NetworkManager::replyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit replyReceived(data);
    } else {
        Logger::error(QString("Network error: %1").arg(reply->errorString()).toStdString());
        emit networkError(reply->errorString());
    }
    reply->deleteLater();
}
