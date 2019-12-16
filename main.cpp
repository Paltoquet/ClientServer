#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "httpserver.h"
#include "soundwavesviewmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SoundWavesViewModel>("Server", 1, 0, "SoundWavesViewModel");
    qmlRegisterType<WaveData>("Server", 1, 0, "WaveData");
    qmlRegisterType<HttpServer>("Server", 1, 0, "HttpServer");

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
