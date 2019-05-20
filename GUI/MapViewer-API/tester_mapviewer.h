#ifndef TESTER_MAPVIEWER_H
#define TESTER_MAPVIEWER_H

#include <QObject>
#include "type_definition.h"

class Tester_MapViewer : public QObject
{
    Q_OBJECT
public:
    explicit Tester_MapViewer(QObject *parent = nullptr);
    Q_INVOKABLE void send_Data(float longitude, float latitude);

signals:
     void incoming_Data(float longitude, float latitude);

public slots:

};

#endif // TESTER_MAPVIEWER_H
