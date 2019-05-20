#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "api_mapviewer.h"
#include "tester_mapviewer.h"
#include "api_guimanager.h"
#include "api_protocolhandler.h"
#include "api_serialhandler.h"

int main(int argc, char *argv[])
{
    // basic set up
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);
        QQuickView viewer;

    // object declaration
        API_GUIManager obj_GUIManager;
        API_MapViewer obj_MapViewer;
        API_SerialHandler obj_SerialHandler;
        API_ProtocolHandler obj_ProtocolHandler;
        Tester_MapViewer obj_testerMapViewer;

    // connection between objects
        QObject::connect(&obj_SerialHandler,&API_SerialHandler::send_DataByte,&obj_ProtocolHandler,&API_ProtocolHandler::receive_DataByte);
        QObject::connect(&obj_ProtocolHandler, &API_ProtocolHandler::send_DataGPS,&obj_GUIManager,&API_GUIManager::receive_Coordinate);
        QObject::connect(&obj_GUIManager, &API_GUIManager::update_UIMap, &obj_MapViewer, &API_MapViewer::receive_Data3DPosition);
        QObject::connect(&obj_testerMapViewer,&Tester_MapViewer::incoming_Data,&obj_MapViewer,&API_MapViewer::receive_Data3DPosition);

    // binding c++ with qml
        viewer.rootContext()->setContextProperty("obj_SerialHandler",&obj_SerialHandler);
        viewer.rootContext()->setContextProperty("obj_testerMapViewer",&obj_testerMapViewer);
        viewer.rootContext()->setContextProperty("obj_MapViewer",&obj_MapViewer);

    // final set up
        viewer.setSource(QUrl("qrc:/main.qml"));
        viewer.show();
    return app.exec();
}
