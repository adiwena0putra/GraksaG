#include "tester_graksastringparser.h"
#include <QDebug>

Tester_GraksaStringParser::Tester_GraksaStringParser(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    QObject::connect(m_timer,&QTimer::timeout,this,&Tester_GraksaStringParser::generate_Data);
    m_timer->start(3000);
}

float Tester_GraksaStringParser::generate_float()
{
    float random = QRandomGenerator::global()->generate()/100000000;
    return  random;
}

double Tester_GraksaStringParser::generate_double()
{
    double random = QRandomGenerator::global()->generate64()/100000000;
    return  random;
}

void Tester_GraksaStringParser::send_float(uint8_t *data)
{
    QByteArray container;
    for (int i=0;i<9;i++) {
        container.append(static_cast<char>(data[i]));
        emit incoming_Data(container);
        container.clear();
    }
}

void Tester_GraksaStringParser::send_double(uint8_t *data)
{
    QByteArray container;
    for (int i=0;i<13;i++) {
        container.append(static_cast<char>(data[i]));
        emit incoming_Data(container);
        container.clear();
    }
}

void Tester_GraksaStringParser::send_string(string str)
{
    QString temp = QString::fromStdString(str);
    QByteArray temp2 = temp.toUtf8();
    emit incoming_Data(temp2);
}

void Tester_GraksaStringParser::generate_Data()
{
    // AX
    float ax = generate_float();
    qDebug()<<"AX_t: "<<ax;
    // AY
    float ay= generate_float();
    qDebug()<<"AY_t: "<<ay;
    // AZ
    float az = generate_float();
    qDebug()<<"AZ_t: "<<az;

    construct_MSG_Accel(ax,ay,az,&m_accelStr);

    // GX
    float gx = generate_float();
    qDebug()<<"GX_t: "<<gx;
    // GY
    float gy = generate_float();
    qDebug()<<"GY_t: "<<gy;
    // GZ
    float gz = generate_float();
    qDebug()<<"GZ_t: "<<gz;

    string temp;
    construct_MSG_Gyro(gx,gy,gz,&temp);
    m_accelStr += "\n" + temp;
    send_string(m_accelStr);

//    // ALT
//    randomfloat = generate_float();
//    construct_MSG_ALT(&message,0xd,m_teamId,randomfloat);
//    qDebug()<<"ALT_t: "<<randomfloat;
//    send_float(message);
//    free(message);
//    // LON
//    double randomdouble = generate_double();
//    construct_MSG_LON(&message,0xd,m_teamId,randomdouble);
//    qDebug()<<"LON_t: "<<randomdouble;
//    send_double(message);
//    free(message);
//    // LAT
//    randomdouble = generate_double();
//    construct_MSG_LAT(&message,0xd,m_teamId,randomdouble);
//    qDebug()<<"LAT_t: "<<randomdouble;
//    send_double(message);
//    free(message);

}
