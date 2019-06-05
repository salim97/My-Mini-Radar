#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mynetwork.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MyNetwork myNetwork ;
    engine.rootContext()->setContextProperty("myNetwork", &myNetwork);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
