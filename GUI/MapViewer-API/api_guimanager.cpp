#include "api_guimanager.h"
#include "QDebug"

API_GUIManager::API_GUIManager(QObject *parent) : QObject(parent)
{
    m_isReplay = false;
    m_isRecord = false;
    m_timer = new QTimer(this);
    QObject::connect(m_timer,&QTimer::timeout,this,&API_GUIManager::update_UIAll);
    m_timer->start(DELAY_TIME);
}

void API_GUIManager::mode_record()
{
    m_isRecord = true;
    m_isReplay = false;
}

void API_GUIManager::mode_replay()
{
    m_isRecord = false;
    m_isReplay = true;
}

void API_GUIManager::receive_DataAccel(float ax, float ay, float az)
{
    m_ax.enqueue(ax);
    m_ay.enqueue(ay);
    m_az.enqueue(az);
}

void API_GUIManager::receive_DataGyro(float gx, float gy, float gz)
{
    m_gx.enqueue(gx);
    m_gy.enqueue(gy);
    m_gz.enqueue(gz);
}

void API_GUIManager::receive_Altitude(float alt)
{
    m_alt.enqueue(alt);
}

void API_GUIManager::receive_Attitude(float roll, float pitch, float yaw)
{
    qDebug()<<"shit";
    m_roll.enqueue(roll);
    m_pitch.enqueue(pitch);
    m_yaw.enqueue(yaw);
}

void API_GUIManager::receive_Odometry(float xpos, float ypos, float zpos)
{
    m_xpos.enqueue(xpos);
    m_ypos.enqueue(ypos);
    m_zpos.enqueue(zpos);
}

void API_GUIManager::receive_Coordinate(float lon, float lat)
{
    m_lon.enqueue(lon);
    m_lat.enqueue(lat);
}

void API_GUIManager::update_UIAll()
{
    //qDebug()<<"update ui!";
    float temp_alt, temp_roll, temp_pitch, temp_yaw, temp_xpos, temp_ypos, temp_zpos;
    float temp_ax, temp_ay, temp_az, temp_gx, temp_gy, temp_gz;
    float temp_lon, temp_lat;
    float temp_apogee = -1;
    // Pengecekan isEmpty dari queue
    if (!m_alt.isEmpty()){
        temp_alt = m_alt.dequeue();
    } else {
        temp_alt = EMPTY_NUMBER;
    }
    if (!m_lon.isEmpty() && !m_lat.isEmpty()){
        temp_lon = m_lon.dequeue();
        temp_lat = m_lat.dequeue();
    } else {
        temp_lon = EMPTY_NUMBER;
        temp_lat = EMPTY_NUMBER;
    }
    if (!m_xpos.isEmpty() && !m_ypos.isEmpty() && !m_zpos.isEmpty()){
        temp_xpos = m_xpos.dequeue();
        temp_ypos = m_ypos.dequeue();
        temp_zpos = m_zpos.dequeue();
    } else {
        temp_xpos = EMPTY_NUMBER;
        temp_ypos = EMPTY_NUMBER;
        temp_zpos = EMPTY_NUMBER;
    }
    if (!m_roll.isEmpty() && !m_pitch.isEmpty() && !m_yaw.isEmpty()){
        temp_roll = m_roll.dequeue();
        temp_pitch = m_pitch.dequeue();
        temp_yaw = m_yaw.dequeue();
    } else {
        temp_roll = EMPTY_NUMBER;
        temp_pitch = EMPTY_NUMBER;
        temp_yaw = EMPTY_NUMBER;
    }
    if (!m_ax.isEmpty() && !m_ay.isEmpty() && !m_az.isEmpty()){
        temp_ax = m_ax.dequeue();
        temp_ay = m_ay.dequeue();
        temp_az = m_az.dequeue();
    } else {
        temp_ax = EMPTY_NUMBER;
        temp_ay = EMPTY_NUMBER;
        temp_az = EMPTY_NUMBER;
    }
    if (!m_gx.isEmpty() && !m_gy.isEmpty() && !m_gz.isEmpty()){
        temp_gx = m_gx.dequeue();
        temp_gy = m_gy.dequeue();
        temp_gz = m_gz.dequeue();
    } else {
        temp_gx = EMPTY_NUMBER;
        temp_gy = EMPTY_NUMBER;
        temp_gz = EMPTY_NUMBER;
    }

    // Storage
    if (m_isRecord){
        emit update_Storage(temp_alt, temp_lon, temp_lat,
                            temp_roll, temp_pitch, temp_yaw,
                            temp_xpos, temp_ypos, temp_zpos,
                            temp_ax, temp_ay, temp_az,
                            temp_gx, temp_gy, temp_gz);
    }
    // Apogee
    if (static_cast<int>(temp_alt) != EMPTY_NUMBER){
        if (temp_alt > temp_apogee) {
            temp_apogee = temp_alt;
            emit update_UIApogee(temp_apogee);
        }
        emit update_UILogF(ALT_LOG_ID, temp_alt);
    }
    // MAP
    if ((static_cast<int>(temp_lon) != EMPTY_NUMBER)
            && (static_cast<int>(temp_lat) != EMPTY_NUMBER)){
        emit update_UILogD(LON_LOG_ID, temp_lon);
        emit update_UILogD(LAT_LOG_ID, temp_lat);
        emit update_UIMap(temp_lon, temp_lat);
    }
    // Scatter
    if ((static_cast<int>(temp_xpos) != EMPTY_NUMBER)
            && (static_cast<int>(temp_ypos) != EMPTY_NUMBER)
            && (static_cast<int>(temp_zpos) != EMPTY_NUMBER)){
        emit update_UILogF(XPOS_LOG_ID, temp_xpos);
        emit update_UILogF(YPOS_LOG_ID, temp_ypos);
        emit update_UILogF(ZPOS_LOG_ID, temp_zpos);
        emit update_UIScatter(temp_xpos, temp_ypos, temp_zpos);
    }
    // Model3d
    if ((static_cast<int>(temp_roll) != EMPTY_NUMBER)
            && (static_cast<int>(temp_pitch) != EMPTY_NUMBER)
            && (static_cast<int>(temp_yaw) != EMPTY_NUMBER)){
        emit update_UILogF(ROLL_LOG_ID, temp_roll);
        emit update_UILogF(PITCH_LOG_ID, temp_pitch);
        emit update_UILogF(YAW_LOG_ID, temp_yaw);
        emit update_UIModel3D(temp_roll, temp_pitch, temp_yaw);
    }
    // Spline
    if ((static_cast<int>(temp_pitch) != EMPTY_NUMBER)
            && (static_cast<int>(temp_xpos) != EMPTY_NUMBER)
            && (static_cast<int>(temp_ypos) != EMPTY_NUMBER)
            && (static_cast<int>(temp_zpos) != EMPTY_NUMBER)){
        emit update_UISpline1(temp_pitch,static_cast<float>(qSqrt(qPow(static_cast<double>(temp_xpos),2) +
                                               qPow(static_cast<double>(temp_ypos),2))),temp_alt);
    }
    // Data Accel
    if ((static_cast<int>(temp_ax) != EMPTY_NUMBER)
            && (static_cast<int>(temp_ay) != EMPTY_NUMBER)
            && (static_cast<int>(temp_az) != EMPTY_NUMBER)){
        //qDebug()<<"update accel log";
        emit update_UILogF(AX_LOG_ID, temp_ax);
        emit update_UILogF(AY_LOG_ID, temp_ay);
        emit update_UILogF(AZ_LOG_ID, temp_az);
        emit update_UISpline2(temp_ax,temp_ay,temp_az);
    }
    // Daya Gyro
    if ((static_cast<int>(temp_gx) != EMPTY_NUMBER)
            && (static_cast<int>(temp_gy) != EMPTY_NUMBER)
            && (static_cast<int>(temp_gz) != EMPTY_NUMBER)){
        emit update_UILogF(GX_LOG_ID, temp_gx);
        emit update_UILogF(GY_LOG_ID, temp_gy);
        emit update_UILogF(GZ_LOG_ID, temp_gz);
        emit update_UISpline3(temp_gx,temp_gy,temp_gz);
    }
}
