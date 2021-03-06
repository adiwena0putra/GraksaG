#ifndef API_STORAGEHANDLER_H
#define API_STORAGEHANDLER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>

class API_StorageHandler : public QObject
{
    Q_OBJECT
public:
    explicit API_StorageHandler(QObject *parent = nullptr);
    void process_line();

signals:
    void notif_ReadData();
    void notif_EndRead();
    void send_Attitude(float roll, float pitch, float yaw);
    void send_Altitude(float alt);
    void send_Coordinate(double lon, double lat);
    void send_Odometry(float xpos, float ypos, float zpos);
    void send_DataAccel(float ax, float ay, float az);
    void send_DataGyro(float gx, float gy, float gz);

public slots:
    void start_Write();
    void start_Read();
    void end_Write();
    void end_Read();
    void update_MissionName(QString missionName);
    void write_Data(float alt, double lon, double lat,
                    float roll, float pitch, float yaw,
                    float xpos, float ypos, float zpos,
                    float ax, float ay, float az,
                    float gx, float gy, float gz);
    void read_Data();

private:
    QString m_missionName;
    QString m_readLine;
    bool m_isRead;
    bool m_isWrite;
    QFile m_file;
    QTextStream m_stream;
};

#endif // API_STORAGEHANDLER_H
