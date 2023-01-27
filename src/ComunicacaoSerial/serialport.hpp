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
    QSerialPort *serial;
    bool serialDeviceConnected;

    void serialDataAvalible();
    void serialRead();    

private: 
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList;
    QStringList infoPortList;
    QString serialBuffer;

    void serialWrite(QString message);
};

#endif // SERIALPORT_HPP
