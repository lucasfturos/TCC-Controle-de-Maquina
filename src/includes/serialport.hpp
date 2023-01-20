#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class SerialPort
{
public:
    SerialPort();
    ~SerialPort();
    void serialConecta();
private:
    QSerialPort *serial;
    QSerialPortInfo *serialinfo;
    QString portName;
};

#endif // SERIALPORT_HPP
