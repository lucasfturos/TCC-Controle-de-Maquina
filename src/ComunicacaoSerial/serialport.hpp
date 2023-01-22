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
    void searchSerialPort();
    QSerialPort *serial;
};

#endif // SERIALPORT_HPP
