#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <tuple>

class ComunicacaoSerial
{
public:
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();
    void serialDataAvalible();
    void serialRead();

private: 
    QSerialPort *serial;
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList, infoPortList;
    QString serialBuffer;
    bool serialDeviceConnected;

    void serialWrite(QString message);
};

#endif // SERIALPORT_HPP
