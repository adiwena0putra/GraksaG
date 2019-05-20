#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickStyle>
#include "api_missionhandler.h"
#include "api_terminal.h"
#include "api_serialhandler.h"
#include "api_protocolhandler.h"
#include "api_dataloghandler.h"
#include "api_guimanager.h"
#include "api_storagehandler.h"
#include "api_mapviewer.h"
#include "api_scatter3d.h"
#include "api_chartviewer.h"
#include "api_modelattitude.h"
//#include "api_graksastringparser.h"

int main(int argc, char *argv[])
{
// basic set up
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");
    QQuickView viewer;

// object declaration
    API_MissionHandler obj_MissionHandler;
    API_Terminal obj_LogMission;
    API_Terminal obj_LogData;
    API_SerialHandler obj_SerialHandler;
    API_ProtocolHandler obj_ProtocolHandler;
//    API_GraksaStringParser obj_GraksaStringParser;
    API_DataLogHandler obj_DataLogHandler;
    API_GUIManager obj_GUIManager;
    API_StorageHandler obj_StorageHandler;
    API_MapViewer obj_MapViewer;
    API_Scatter3D obj_Scatter3D;
    API_ChartViewer obj_ChartViewerRangeAlt;
    API_ChartViewer obj_ChartViewerAccel;
    API_ChartViewer obj_ChartViewerGyro;
    API_ModelAttitude obj_ModelAttitude;

// connection between objects
    // koneksi ui ke Qt untuk fungsi quit
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    // koneksi MissionHandler ke StorageHandler untuk filename, tanda record or replay
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::send_MissionName,&obj_StorageHandler,&API_StorageHandler::update_MissionName);
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::command_StartDataAcq,&obj_StorageHandler,&API_StorageHandler::start_Write);
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::command_StopDataAcq,&obj_StorageHandler,&API_StorageHandler::end_Write);
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::command_ReplayMission,&obj_StorageHandler,&API_StorageHandler::start_Read);

    // koneksi MissionHandler ke GUIManager untuk mode record or replay
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::command_StartDataAcq,&obj_GUIManager,&API_GUIManager::mode_record);
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::command_ReplayMission,&obj_GUIManager,&API_GUIManager::mode_replay);

    // koneksi MissionHandler ke LogMission untuk notif
    QObject::connect(&obj_MissionHandler,&API_MissionHandler::notif_Log,&obj_LogMission,&API_Terminal::receive_Message);

    // koneksi SerialHandler ke LogMission untuk notif
    QObject::connect(&obj_SerialHandler,&API_SerialHandler::message_SerialHandler,&obj_LogMission,&API_Terminal::receive_Message);

    // koneksi SerialHandler ke ProtocolHandler untuk kirim byte
    QObject::connect(&obj_SerialHandler,&API_SerialHandler::send_DataByte,&obj_ProtocolHandler,&API_ProtocolHandler::receive_DataByte);
//    QObject::connect(&obj_SerialHandler,&API_SerialHandler::send_DataByte,&obj_GraksaStringParser,&API_GraksaStringParser::receive_DataByte);

    // koneksi ProtocolHandler ke GUIManager untuk data accel dan gyro
    QObject::connect(&obj_ProtocolHandler, &API_ProtocolHandler::send_DataAccel,&obj_GUIManager,&API_GUIManager::receive_DataAccel);
    QObject::connect(&obj_ProtocolHandler, &API_ProtocolHandler::send_DataGyro,&obj_GUIManager,&API_GUIManager::receive_DataGyro);
    QObject::connect(&obj_ProtocolHandler, &API_ProtocolHandler::send_DataAttitude,&obj_GUIManager,&API_GUIManager::receive_Attitude);
    QObject::connect(&obj_ProtocolHandler, &API_ProtocolHandler::send_DataGPS,&obj_GUIManager,&API_GUIManager::receive_Coordinate);

//    QObject::connect(&obj_GraksaStringParser, &API_GraksaStringParser::send_DataAccel,&obj_GUIManager,&API_GUIManager::receive_DataAccel);
//    QObject::connect(&obj_GraksaStringParser, &API_GraksaStringParser::send_DataGyro,&obj_GUIManager,&API_GUIManager::receive_DataGyro);

    // koneksi GUIManager ke datalog handler untuk data float dan double
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UILogF, &obj_DataLogHandler,&API_DataLogHandler::receive_DataLogF);
//    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UILogD, &obj_DataLogHandler,&API_DataLogHandler::receive_DataLogD);

    // koneksi GUIManager ke storage hanler untuk ngasih data
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_Storage, &obj_StorageHandler,&API_StorageHandler::write_Data);

    // koneksi storage handler ke GUIManager untuk ngasih data hasil read
    QObject::connect(&obj_StorageHandler, &API_StorageHandler::send_DataAccel, &obj_GUIManager,&API_GUIManager::receive_DataAccel);
    QObject::connect(&obj_StorageHandler, &API_StorageHandler::send_DataGyro, &obj_GUIManager,&API_GUIManager::receive_DataGyro);

    // koneksi storage handler ke mission handler untuk notif selesai replay
    QObject::connect(&obj_StorageHandler, &API_StorageHandler::notif_EndRead, &obj_MissionHandler,&API_MissionHandler::notif_EndReplay);

    // koneksi datalog handler ke datalog untuk notif
    QObject::connect(&obj_DataLogHandler, &API_DataLogHandler::message_DataLog, &obj_LogData,&API_Terminal::receive_Message);

    // koneksi guiManager ke ui element
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UIMap, &obj_MapViewer, &API_MapViewer::receive_DataCoordinate);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UIScatter, &obj_Scatter3D, &API_Scatter3D::receive_Data3DPosition);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UISpline1, &obj_ChartViewerRangeAlt, &API_ChartViewer::receive_DataSpline);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UISpline2, &obj_ChartViewerAccel, &API_ChartViewer::receive_DataSpline_3Data);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UISpline3, &obj_ChartViewerGyro, &API_ChartViewer::receive_DataSpline_3Data);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UIModel3D, &obj_ModelAttitude, &API_ModelAttitude::receive_Attitude);
    QObject::connect(&obj_GUIManager, &API_GUIManager::update_UIScatter, &obj_Scatter3D, &API_Scatter3D::receive_Data3DPosition);

// binding c++ with qml
    viewer.rootContext()->setContextProperty("obj_MissionHandler",&obj_MissionHandler);
    viewer.rootContext()->setContextProperty("obj_LogMission",&obj_LogMission);
    viewer.rootContext()->setContextProperty("obj_LogData",&obj_LogData);
    viewer.rootContext()->setContextProperty("obj_SerialHandler",&obj_SerialHandler);
    viewer.rootContext()->setContextProperty("obj_DataLogHandler",&obj_DataLogHandler);
    viewer.rootContext()->setContextProperty("obj_MapViewer",&obj_MapViewer);
    viewer.rootContext()->setContextProperty("obj_Scatter3D",&obj_Scatter3D);
    viewer.rootContext()->setContextProperty("obj_ChartViewerRangeAlt",&obj_ChartViewerRangeAlt);
    viewer.rootContext()->setContextProperty("obj_ChartViewerAccel",&obj_ChartViewerAccel);
    viewer.rootContext()->setContextProperty("obj_ChartViewerGyro",&obj_ChartViewerGyro);
    viewer.rootContext()->setContextProperty("obj_ModelAttitude",&obj_ModelAttitude);

// final set up
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.showFullScreen();
    //viewer.showMaximized();

    return app.exec();
}
