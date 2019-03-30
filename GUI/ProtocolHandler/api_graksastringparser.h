#ifndef API_GRAKSASTRINGPARSER_H
#define API_GRAKSASTRINGPARSER_H

#include <QObject>
#include <QByteArray>
#include <QQueue>
#include "graksastring.h"

class API_GraksaStringParser : public QObject
{
    Q_OBJECT
public:
    explicit API_GraksaStringParser(QObject *parent = nullptr);

signals:
    void send_DataAccel(float ax, float ay, float az);
    void send_DataGyro(float gx, float gy, float gz);
    void send_DataGPS(double lon, double lan);
    void send_DataAltitude(float alt);

public slots:
    void receive_DataByte(QByteArray data);
    void set_TeamId (QString id);

private:
    QString m_teamId;
    QString m_temp;
};

#endif // API_GRAKSASTRINGPARSER_H
