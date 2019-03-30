#ifndef TESTER_GRAKSASTRINGPARSER_H
#define TESTER_GRAKSASTRINGPARSER_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include "graksastring.h"

class Tester_GraksaStringParser : public QObject
{
    Q_OBJECT
public:
    explicit Tester_GraksaStringParser(QObject *parent = nullptr);
    float generate_float();
    double generate_double();
    void send_float(uint8_t *data);
    void send_double(uint8_t *data);
    void send_string(string str);

signals:
    void incoming_Data(QByteArray data);

public slots:
    void generate_Data();

private:
    QTimer *m_timer;
    string m_accelStr;
};

#endif // TESTER_GRAKSASTRINGPARSER_H
