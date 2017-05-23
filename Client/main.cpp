#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "clientnetworkinterface.h"
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ClientNetworkInterface>("extend.qt.ClientNetworkInterface", 1, 0, "ClientNetworkInterface");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:///main.qml"));
    viewer.show();
    */

    return app.exec();
}
