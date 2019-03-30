#ifndef API_PROTOCOLHANDLER_H
#define API_PROTOCOLHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QQueue>

extern "C"{
    #include "graksalink.h"
}

class API_ProtocolHandler : public QObject
{
    Q_OBJECT
public:
    explicit API_ProtocolHandler(QObject *parent = nullptr);
    void emiter_DataAccel();
    void emiter_DataGyro();
    void emiter_DataGPS();
    void emiter_Attitude();

signals:
    void send_DataAccel(float ax, float ay, float az);
    void send_DataGyro(float gx, float gy, float gz);
    void send_DataGPS(double lon, double lan);
    void send_DataAttitude(float roll, float pitch, float yaw);
    void send_DataAltitude(float alt);
    void send_DataCamera();

public slots:
    void receive_DataByte(QByteArray data);
    void set_TeamId (QString id);

private:
    int m_byteCounter;
    int m_maxCounter;
    uint m_axTag;
    uint m_ayTag;
    uint m_azTag;
    uint m_gxTag;
    uint m_gyTag;
    uint m_gzTag;
    uint m_lonTag;
    uint m_latTag;
    uint m_rollTag;
    uint m_pitchTag;
    uint m_yawTag;
    QByteArray m_data;
    uint8_t m_teamId[3];
    uint8_t m_msgId;
    QQueue<float> m_ax;
    QQueue<float> m_ay;
    QQueue<float> m_az;
    QQueue<float> m_gx;
    QQueue<float> m_gy;
    QQueue<float> m_gz;
    QQueue<float> m_alt;
    QQueue<float> m_xpos;
    QQueue<float> m_ypos;
    QQueue<float> m_zpos;
    QQueue<float> m_roll;
    QQueue<float> m_pitch;
    QQueue<float> m_yaw;
    QQueue<double> m_lon;
    QQueue<double> m_lat;
};

#endif // API_PROTOCOLHANDLER_H
