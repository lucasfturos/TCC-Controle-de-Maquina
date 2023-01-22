#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class ComunicacaoSerial
{
public:
    ComunicacaoSerial();
    ~ComunicacaoSerial();
    void searchDevice();
private:
    QSerialPort *serial;
    QSerialPortInfo *serialinfo;
};

#endif // SERIALPORT_HPP
