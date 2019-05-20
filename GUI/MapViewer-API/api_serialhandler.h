#ifndef API_SERIALHANDLER_H
#define API_SERIALHANDLER_H

#define BYTES_PER_READ 1

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

class API_SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit API_SerialHandler(QObject *parent = nullptr);
    Q_INVOKABLE void open_serial();
    Q_INVOKABLE void close_serial();
    Q_INVOKABLE void scan_serial();
    Q_INVOKABLE void set_serial(QString selected);
    Q_INVOKABLE void set_baud(qint32 baud);
    Q_INVOKABLE void set_databits(int databits);
    Q_INVOKABLE void set_parity(int parity);
    Q_INVOKABLE void set_stopbits(int stopbits);
    Q_INVOKABLE void start_DataAcq();
    Q_INVOKABLE void stop_DataAcq();

signals:
    void message_SerialHandler(QString message);
    void send_DataByte(QByteArray data);
    void changed_List();
    void update_UI(QString port_name);

public slots:
    void read_DataBytes();
    void write_DataBytes(QByteArray data);
    void update_List();


private:
    QString m_message;
    bool m_isActive;
    bool m_isDataAcq;
    QSerialPort m_serial;
    QList<QSerialPortInfo> m_infos;
    QByteArray m_data;
};

#endif // API_SERIALHANDLER_H
