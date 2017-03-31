#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "searchlist.h"
#include <QQmlEngine>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    SearchList Obj;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("searchObj",&Obj);
    return app.exec();
}
