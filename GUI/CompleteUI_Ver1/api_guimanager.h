#ifndef API_GUIMANAGER_H
#define API_GUIMANAGER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QtMath>
#include "define_gui.h"

class API_GUIManager : public QObject
{
    Q_OBJECT
public:
    explicit API_GUIManager(QObject *parent = nullptr);

signals:
    void update_UIScatter(float xpos, float ypos, float zpos);
    void update_UISpline1(float launch_angle, float range, float alt);
    void update_UILog(int id, float data);
    void update_UILog(int id, double data);
    void update_UIMap(double lon, double lat);
    void update_UIModel3D(float roll, float pitch, float yaw);
    void update_UIApogee(float apogee);
    void update_Storage(float alt, double lon, double lat,
                        float roll, float pitch, float yaw,
                        float xpos, float ypos, float zpos);

public slots:
    void update_UIAll();
    void receive_Attitude(float roll, float pitch, float yaw);
    void receive_Altitude(float alt);
    void receive_Coordinate(double lon, double lat);
    void receive_Odometry(float xpos, float ypos, float zpos);
    void receive_DataAccel(float ax, float ay, float az);
    void receive_DataGyro(float gx, float gy, float gz);
    void mode_replay();
    void mode_record();

private:
    bool m_isReplay;
    bool m_isRecord;
    QTimer* m_timer;
    QQueue<float> m_ax;
    QQueue<float> m_ay;
    QQueue<float> m_az;
    QQueue<float> m_gx;
    QQueue<float> m_gy;
    QQueue<float> m_gz;
    QQueue<float> m_roll;
    QQueue<float> m_pitch;
    QQueue<float> m_yaw;
    QQueue<float> m_alt;
    QQueue<float> m_xpos;
    QQueue<float> m_ypos;
    QQueue<float> m_zpos;
    QQueue<double> m_lon;
    QQueue<double> m_lat;
};

#endif // API_GUIMANAGER_H
