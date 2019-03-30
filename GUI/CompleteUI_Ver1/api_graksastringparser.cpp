#include "api_graksastringparser.h"
#include <QDebug>

API_GraksaStringParser::API_GraksaStringParser(QObject *parent) : QObject(parent)
{
    m_teamId = "13ITB";
}

void API_GraksaStringParser::receive_DataByte(QByteArray data)
{
    QString temp(data);
    qDebug()<<temp;
    QStringList listSensor = temp.split("\n");
    QStringList listData;
    for (int i=0; i<listSensor.size(); i++){
        listData = listSensor[i].split(";");
        if (listData.size()>=3) {
            if (listData[0]=="13ITB"){
                int dataID = listData[1].toInt();
                switch (dataID) {
                case GRAKSA_MSG_ID_ACCEL:
                    if (listData.size()==5) {
                        send_DataAccel(listData[2].toFloat(),listData[3].toFloat(),listData[4].toFloat());
//                        qDebug()<<"GRAKSA_MSG_ID_ACCEL: "<<listData[2].toFloat();
                    }
                    break;
                case GRAKSA_MSG_ID_GYRO:
                    if (listData.size()==5) {
                        send_DataGyro(listData[2].toFloat(),listData[3].toFloat(),listData[4].toFloat());
//                        qDebug()<<"GRAKSA_MSG_ID_GYRO: "<<listData[2].toFloat();
                    }
                    break;
                case GRAKSA_MSG_ID_ALT:
                    if (listData.size()==3) {
                        send_DataAltitude(listData[2].toFloat());
                    }
                    break;
                case GRAKSA_MSG_ID_GPS:
                    if (listData.size()==4) {
                        send_DataGPS(listData[2].toDouble(),listData[3].toDouble());
                    }
                    break;
                }
            }
        }
    }
}

void API_GraksaStringParser::set_TeamId(QString id)
{
    m_teamId = id;
}
