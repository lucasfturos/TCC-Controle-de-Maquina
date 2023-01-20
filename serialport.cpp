#include "serialport.hpp"

void SerialPort::serialConecta(){
    serial->setPortName(portName);
    qDebug()<<serial->errorString();

    if (serial->open(QIODevice::ReadWrite)){
        if (!serial->setBaudRate(QSerialPort::Baud9600)){
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

SerialPort::~SerialPort()
{
    serial->close();
}
