#include "engine.h"
#include <QGuiApplication>
#include <QObject>


int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine qEngine;

    Engine engine(qEngine);
    QObject::connect(&a, &QGuiApplication::aboutToQuit, &engine, &Engine::onQuit);
    engine.init(argc, argv);

    return a.exec();
}
