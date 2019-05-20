QT += quick widgets quickcontrols2 datavisualization gui qml core charts serialport
# 3dcore 3drender 3dinput 3dlogic 3dextras qml quick 3dquick 3danimation

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    api_missionhandler.cpp \
    api_serialhandler.cpp \
    api_terminal.cpp \
    api_protocolhandler.cpp \
    graksalink.c \
    api_guimanager.cpp \
    api_dataloghandler.cpp \
    api_modelattitude.cpp \
    api_storagehandler.cpp \
    api_mapviewer.cpp \
    api_scatter3d.cpp \
    api_chartviewer.cpp \
    graksastring.cpp \
    api_graksastringparser.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    api_missionhandler.h \
    api_serialhandler.h \
    api_terminal.h \
    api_protocolhandler.h \
    graksalink.h \
    api_guimanager.h \
    define_gui.h \
    api_dataloghandler.h \
    api_modelattitude.h \
    api_storagehandler.h \
    api_mapviewer.h \
    api_scatter3d.h \
    api_chartviewer.h \
    graksastring.h \
    api_graksastringparser.h
