#ifndef API_MAPVIEWER_H
#define API_MAPVIEWER_H

#include <QObject>
#include "type_definition.h"

class API_MapViewer : public QObject
{
    Q_OBJECT
public:
    explicit API_MapViewer(QObject *parent = nullptr);
    Q_INVOKABLE void set_home();
    Q_INVOKABLE void set_clear();

signals:
    void update_UI(float longitude, float latitude, bool isHome);
    void message_MapViewer(QString message);

public slots:
    void receive_Data3DPosition(float longitude, float latitude);

private:
    bool m_isHome;
    bool m_isClear;
    QString m_message;
};

#endif // API_MAPVIEWER_H
