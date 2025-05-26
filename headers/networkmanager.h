#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QObject *parent = nullptr);
    ~NetworkManager() {
        if (manager)
            delete manager;
    }

    Q_INVOKABLE void sendRequest(const QString &url);

    signals:
    void replyReceived(const QByteArray &data);
    void networkError(const QString &error);

    public slots:
    void replyFinished(QNetworkReply *reply);

    private:
    QNetworkAccessManager *manager;
};

#endif // NETWORKMANAGER_H
