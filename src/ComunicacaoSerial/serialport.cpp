#include "serialport.hpp"

void ComunicacaoSerial::searchDevice(){
    serial->setPortName("/dev/tty0");
    qDebug()<<serial->errorString();

    if (serial->open(QIODevice::ReadWrite)){
        if (!serial->setBaudRate(QSerialPort::Baud2400)){
            qDebug()<<serial->errorString();
        }
        if (!serial->setDataBits(QSerialPort::Data8)){
            qDebug()<<serial->errorString();
        }
        if (!serial->setParity(QSerialPort::NoParity)){
            qDebug()<<serial->errorString();
        }
        if (!serial->setStopBits(QSerialPort::OneStop)){
            qDebug()<<serial->errorString();
        }
        if (!serial->setFlowControl(QSerialPort::NoFlowControl)){
            qDebug()<<serial->errorString();
        }
        if(serial->waitForReadyRead(100)){
            qDebug()<<"Response: "<<serial->readAll();
        } else {
            qDebug()<<"Time out";
        }
    } else{
        qDebug()<<"Serial port not opened. Error: "<<serial->errorString();
    }
}

ComunicacaoSerial::~ComunicacaoSerial()
{
    serial->close();
}
