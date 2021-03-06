#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "api_protocolhandler.h"
#include "tester_protocolhandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    API_ProtocolHandler obj_ProtocolHandler;
    Tester_ProtocolHandler obj_Tester;

    QObject::connect(&obj_Tester,&Tester_ProtocolHandler::incoming_Data,&obj_ProtocolHandler,&API_ProtocolHandler::receive_DataByte);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
