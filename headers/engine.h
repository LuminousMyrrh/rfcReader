#ifndef ENGINE_H
#define ENGINE_H

#include "networkmanager.h"
#include "rfcworker.h"
#include "settings.h"
#include <QObject>
#include <QQmlApplicationEngine>

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(QQmlApplicationEngine &qmlEngine, QObject *parent = nullptr);

    void init(int argc, char *argv[]);
    void onQuit();

public slots:
    void rfcReceived(const QByteArray &data);
    //void networkError(const QString &error);

private:
    QQmlApplicationEngine &qmlEngine;
    NetworkManager *nwManager;
    RfcWorker *rfcWorker;
    Settings *settings;
};

#endif // ENGINE_H
