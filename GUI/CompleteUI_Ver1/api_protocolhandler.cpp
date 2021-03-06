#include "api_protocolhandler.h"
#include <QtDebug>

API_ProtocolHandler::API_ProtocolHandler(QObject *parent) : QObject(parent)
{
    m_axTag = 0;
    m_ayTag = 0;
    m_azTag = 0;
    m_gxTag = 0;
    m_gyTag = 0;
    m_gzTag = 0;
    m_lonTag = 0;
    m_latTag = 0;
    m_altTag = 0;
    m_teamId[0]='I';
    m_teamId[1]='T';
    m_teamId[2]='B';
    m_msgId = 99;
    m_byteCounter = 0;
    m_maxCounter = 999;
}

void API_ProtocolHandler::emiter_DataAccel()
{
    if ((m_axTag == m_ayTag)&&(m_axTag == m_azTag)&&(m_ayTag == m_azTag)) {
        emit send_DataAccel(m_ax.dequeue(),m_ay.dequeue(),m_az.dequeue());
    } else {
        m_axTag = 0;
        m_ayTag = 0;
        m_azTag = 0;
        m_ax.clear();
        m_ay.clear();
        m_az.clear();
    }
}

void API_ProtocolHandler::emiter_DataGyro()
{
    if ((m_gxTag == m_gyTag)&&(m_gxTag == m_gzTag)&&(m_gyTag == m_gzTag)) {
        emit send_DataGyro(m_gx.dequeue(),m_gy.dequeue(),m_gz.dequeue());
    } else {
        m_gxTag = 0;
        m_gyTag = 0;
        m_gzTag = 0;
        m_gx.clear();
        m_gy.clear();
        m_gz.clear();
    }
}

void API_ProtocolHandler::emiter_DataGPS()
{
    if ((m_lonTag == m_latTag)&&(m_lonTag == m_altTag)&&(m_altTag == m_latTag)) {
        emit send_DataGPS(m_lon.dequeue(),m_lat.dequeue(),m_alt.dequeue());
    } else {
        m_lonTag = 0;
        m_latTag = 0;
        m_altTag = 0;
        m_lon.clear();
        m_lat.clear();
        m_alt.clear();
    }
}

void API_ProtocolHandler::emiter_Attitude()
{
    if ((m_rollTag == m_pitchTag)&&(m_rollTag == m_yawTag)&&(m_pitchTag == m_yawTag)){
        //qDebug()<<"yeah";
        emit send_DataAttitude(m_roll.dequeue(),m_pitch.dequeue(),m_yaw.dequeue());
    } else {
        m_rollTag = 0;
        m_pitchTag = 0;
        m_yawTag = 0;
        m_roll.clear();
        m_pitch.clear();
        m_yaw.clear();
    }
}

void API_ProtocolHandler::receive_DataByte(QByteArray data)
{
    bool startNewFrame = false;
    for (int i=0; i<data.size() ;i++) {
        if (static_cast<uint8_t>(data[i]) == 0xd) {
            startNewFrame = true;
            m_data.clear();
            m_byteCounter = 0;
            m_maxCounter = 999;
        } else {
            startNewFrame = false;
        }
        if (startNewFrame){
            m_data.append(data[i]);
            m_byteCounter++;
        } else {
            switch (m_byteCounter) {
            case 1:
                if (static_cast<uint8_t>(data[i]) == m_teamId[0]) {
                    m_data.append(data[i]);
                    m_byteCounter++;
                    break;
                } else {
                    m_byteCounter = 0;
                    m_data.clear();
                    break;
                }
            case 2:
                if (static_cast<uint8_t>(data[i]) == m_teamId[1]) {
                    m_data.append(data[i]);
                    m_byteCounter++;
                    break;
                } else {
                    m_byteCounter = 0;
                    m_data.clear();
                    break;
                }
            case 3:
                if (static_cast<uint8_t>(data[i]) == m_teamId[2]) {
                    m_data.append(data[i]);
                    m_byteCounter++;
                    break;
                } else {
                    m_byteCounter = 0;
                    m_data.clear();
                    break;
                }
            case 4:
                if ((m_msgId = static_cast<uint8_t>(data[i])) <= 16) {
                    m_maxCounter = m_byteCounter + 4; // float
                    m_data.append(data[i]);
                    m_byteCounter++;
                    break;
                } else {
                    m_byteCounter = 0;
                    m_data.clear();
                    break;
                }
            default:
                m_data.append(data[i]);
                m_byteCounter++;
                if (m_byteCounter == 0) {
                    break;
                } else {
                    if (m_byteCounter == m_maxCounter+1) {
                        float container;
                        char*p_payload;
                        p_payload = m_data.data();
                        switch (m_msgId) {
                        case GRAKSA_MSG_ID_AX:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"AX: "<<container;
                            m_ax.enqueue(container);
                            m_axTag += 1;
                            break;
                        case GRAKSA_MSG_ID_AY:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"AY: "<<container;
                            m_ay.enqueue(container);
                            m_ayTag += 1;
                            break;
                        case GRAKSA_MSG_ID_AZ:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"AZ: "<<container;
                            m_az.enqueue(container);
                            m_azTag += 1;
                            emiter_DataAccel();
                            break;
                        case GRAKSA_MSG_ID_GX:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"GX: "<<container;
                            m_gx.enqueue(container);
                            m_gxTag += 1;
                            break;
                        case GRAKSA_MSG_ID_GY:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"GY: "<<container;
                            m_gy.enqueue(container);
                            m_gyTag += 1;
                            break;
                        case GRAKSA_MSG_ID_GZ:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"GZ: "<<container;
                            m_gz.enqueue(container);
                            m_gzTag += 1;
                            emiter_DataGyro();
                            break;
                        case GRAKSA_MSG_ID_ALT:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"ALT: "<<container;
                            m_alt.enqueue(container);
                            m_altTag += 1;
                            //emit send_DataAltitude(m_alt.dequeue());
                            break;
                        case GRAKSA_MSG_ID_LON:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"LON: "<<container;
                            m_lon.enqueue(container);
                            m_lonTag += 1;
                            break;
                        case GRAKSA_MSG_ID_LAT:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            //qDebug()<<"LAT: "<<container;
                            m_lat.enqueue(container);
                            m_latTag += 1;
                            emiter_DataGPS();
                            break;
                        case GRAKSA_MSG_ID_PHOTO:
                            // masih gatau
                            break;
                        case GRAKSA_MSG_ID_XPOS:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            m_xpos.enqueue(container);
                            break;
                        case GRAKSA_MSG_ID_YPOS:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            m_ypos.enqueue(container);
                            break;
                        case GRAKSA_MSG_ID_ZPOS:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            m_zpos.enqueue(container);
                            break;
                        case GRAKSA_MSG_ID_ROLL:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            qDebug()<<"ROLL: "<<container;
                            m_roll.enqueue(container);
                            m_rollTag += 1;
                            break;
                        case GRAKSA_MSG_ID_PITCH:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            qDebug()<<"PITCH: "<<container;
                            m_pitch.enqueue(container);
                            m_pitchTag += 1;
                            break;
                        case GRAKSA_MSG_ID_YAW:
                            memcpy(&container, &(p_payload[5]), sizeof (float));
                            qDebug()<<"YAW: "<<container;
                            m_yaw.enqueue(container);
                            m_yawTag += 1;
                            emiter_Attitude();
                            break;
                        default:
                            // should never be here
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void API_ProtocolHandler::set_TeamId(QString id)
{
    QByteArray convertion = id.toLocal8Bit();
    for (int i=0; i<3; i++){
        m_teamId[i] = static_cast <uint8_t> (convertion[i]);
    }
}
