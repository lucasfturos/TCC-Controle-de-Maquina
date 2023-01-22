#include "serialport.hpp"


void ComunicacaoSerial::searchSerialPort(){
    int i =0;
    QStringList ports;
    const auto serialAvaiblePorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialInfo : serialAvaiblePorts){
        ports.insert(i, serialInfo.portName());
        i++;
    }
    qDebug()<<serial->errorString();

}

ComunicacaoSerial::~ComunicacaoSerial()
{
    serial->close();
}
