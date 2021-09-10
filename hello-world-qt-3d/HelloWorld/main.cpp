#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myquickview.h"
#include "myquickitem.h"
#include "simulation.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<MyQuickView>("com.example.MyQuickView", 1, 0, "MyQuickView");
    qmlRegisterType<MyQuickItem>("com.example.MyQuickItem", 1, 0, "MyQuickItem");

    qmlRegisterType<Simulation>("com.example.Simulation", 1, 0, "Simulation");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/init.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
