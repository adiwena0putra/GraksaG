#include "api_mapviewer.h"
#include <QDebug>

API_MapViewer::API_MapViewer(QObject *parent) : QObject(parent)
{
    m_isHome = false;
    m_isClear = true;
}

void API_MapViewer::set_home()
{
    if (m_isClear) {
        m_isHome = true;
        m_isClear = false;
        m_message = "SUCCED: Home berhasil diset.";
        emit message_MapViewer(m_message);
        //qDebug()<<m_isHome;
    } else {
        m_message = "FAILED: Clear MapViewer saat ini terlebih dahulu.";
        emit message_MapViewer(m_message);
    }
}

void API_MapViewer::set_clear()
{
    if (!m_isClear) {
        m_isClear = true;
    }
}

// SLOT
void API_MapViewer::receive_DataCoordinate(double longitude, double latitude)
{
    //qDebug()<<"emit update_UI ";
    emit update_UI(longitude, latitude, m_isHome);
    if (m_isHome) {
        m_isHome = false;
    }
}
