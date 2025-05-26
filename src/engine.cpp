#include "engine.h"
#include "networkmanager.h"
#include "logger.h"
#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>

Engine::Engine(QQmlApplicationEngine &qmlEngine, QObject *parent)
    : qmlEngine(qmlEngine), rfcWorker(nullptr), QObject(parent) {
    nwManager = new NetworkManager(this);
    settings = new Settings(this);
    rfcWorker = new RfcWorker(&qmlEngine);
}

void Engine::init(int argc, char *argv[]) {
    connect(nwManager, &NetworkManager::replyReceived,
            this, &Engine::rfcReceived);

    qmlEngine.rootContext()->setContextProperty("rfcWorker", rfcWorker);
    qmlEngine.rootContext()->setContextProperty("networkManager", nwManager);

    Logger::info("Loading qml");
    const QUrl url("qrc:/main.qml");
    connect(&qmlEngine, &QQmlApplicationEngine::objectCreated, this, [this, url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            qCritical() << "Failed to load QML file:" << url;
            QCoreApplication::exit(-1);
        } else if (obj && url == objUrl) {
            int lastRfc = settings->getLastRfc();

            if (lastRfc != -1 && lastRfc != 0) {
                Logger::info("Opening last saved rfc");
                rfcWorker->setCurrentRfcNumber(lastRfc);
                int lastPage = settings->getLastPage();
                nwManager->sendRequest(QString("https://www.rfc-editor.org/rfc/rfc%1.txt")
                                          .arg(lastRfc));
                if (lastPage != -1) {
                    Logger::info(QString("Setting last saved page: %1").arg(QString::number(lastPage)).toStdString());
                    rfcWorker->setCurrentRfcPage(lastPage);
                }
            }
        }
    });
    qmlEngine.load(url);
}
void Engine::rfcReceived(const QByteArray &data) {
    Logger::info("Data received");
    rfcWorker->setRfcText(QString::fromUtf8(data));
}

void Engine::onQuit() {
    Logger::info("Saving last rfc");
    settings->setLastRfc(rfcWorker->getCurrentRfcNumber());
    Logger::info("Saving last rfc page");
    settings->setLastPage(rfcWorker->getCurrentRfcPage());
}
