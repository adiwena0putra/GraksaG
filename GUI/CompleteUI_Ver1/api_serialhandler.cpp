#include "api_serialhandler.h"
//#include <QtDebug>

API_SerialHandler::API_SerialHandler(QObject *parent) : QObject(parent)
{
    m_isActive = false;
    m_isDataAcq = false;
    connect(this,&API_SerialHandler::changed_List,this,&API_SerialHandler::update_List);
    connect(&m_serial,&QSerialPort::readyRead,this,&API_SerialHandler::read_DataBytes);
//    connect(this,SIGNAL(changed_List()),this,SLOT(update_List()));
//    connect(&m_serial,SIGNAL(readyRead()),this,SLOT(read_DataBytes()));
}

void API_SerialHandler::open_serial()
{
    if (!m_isActive) {
        if (m_infos.count() != 0) {
            if (m_serial.open(QIODevice::ReadWrite)) {
                m_isActive = true;
                m_message = "SUCCED: Koneksi serial baru berhasil dibuat.";
                emit message_SerialHandler(m_message);
            } else {
                m_message = "FAILED: Gagal membuat koneksi, silakan scan lagi port anda.";
                emit message_SerialHandler(m_message);
            }
        } else {
            m_message = "FAILED: Tidak ada port yang tersedia.";
            emit message_SerialHandler(m_message);
        }
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::close_serial()
{
    if (m_isActive) {
        m_serial.close();
        m_isActive = false;
        m_message = "SUCCED: Koneksi serial berhasil diputuskan.";
        emit message_SerialHandler(m_message);
    } else {
        m_message = "FAILED: Tidak ada koneksi serial untuk diputuskan.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::scan_serial()
{
    if (!m_isActive) {
        m_infos.clear();
        auto infos = QSerialPortInfo::availablePorts();
        if (infos.count() != 0) {
            for (int i = 0; i < infos.count(); i++) {
                m_infos.append(infos[i]);
            }
            emit changed_List();
        } else {
            emit update_UI("zero");
        }
        m_message = "SUCCED: Scanning serial port selesai.";
        emit message_SerialHandler(m_message);
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::set_serial(QString selected)
{
    if (!m_isActive) {
        int i = 0;
        while (selected != m_infos[i].portName()) {
            i++;
        }
        m_message = "SUCCED: Port berhasil diset.";
        emit message_SerialHandler(m_message);
        m_serial.setPort(m_infos[i]);
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::set_baud(qint32 baud)
{
    if (!m_isActive) {
        m_serial.setBaudRate(baud);
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::set_databits(int databits)
{
    if (!m_isActive) {
        switch (databits) {
        case 5: m_serial.setDataBits(QSerialPort::Data5);break;
        case 6: m_serial.setDataBits(QSerialPort::Data6);break;
        case 7: m_serial.setDataBits(QSerialPort::Data7);break;
        case 8: m_serial.setDataBits(QSerialPort::Data8);break;
        }
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::set_parity(int parity)
{
    if (!m_isActive) {
        switch (parity) {
        case 0: m_serial.setParity(QSerialPort::NoParity);break;
        case 1: m_serial.setParity(QSerialPort::OddParity);break;
        case 2: m_serial.setParity(QSerialPort::EvenParity);break;
        }
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

void API_SerialHandler::set_stopbits(int stopbits)
{
    if (!m_isActive) {
        switch (stopbits) {
        case 1: m_serial.setStopBits(QSerialPort::OneStop);break;
        case 2: m_serial.setStopBits(QSerialPort::TwoStop);break;
        }
    } else {
        m_message = "FAILED: Putuskan koneksi saat ini terlebih dahulu.";
        emit message_SerialHandler(m_message);
    }
}

// SLOT

void API_SerialHandler::update_List()
{
    for (int i= 0 ; i<m_infos.count() ; i++) {
        emit update_UI(m_infos[i].portName());
    }
}

void API_SerialHandler::read_DataBytes()
{
    if (m_serial.bytesAvailable()) {
        m_data = m_serial.readAll();
//        qDebug()<<m_data;
        if (m_isDataAcq){
            emit send_DataByte(m_data);
            m_data.clear();
        }
    }

}

void API_SerialHandler::write_DataBytes(QByteArray data)
{
    m_serial.write(data);
}

void API_SerialHandler::start_DataAcq()
{
//    qDebug()<<"start data acq";
    m_isDataAcq = true;
}

void API_SerialHandler::stop_DataAcq()
{
//    qDebug()<<"stop data acq";
    m_isDataAcq = false;
}
