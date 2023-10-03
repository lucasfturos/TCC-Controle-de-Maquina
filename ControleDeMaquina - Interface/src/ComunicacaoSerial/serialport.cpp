#include "serialport.hpp"

std::tuple<QStringList, QStringList>
ComunicacaoSerial::getAvalilableSerialDevice() {
    qDebug() << "Número de portas disponiveis: "
             << serialInfo->availablePorts().length();

    infoBaudList << "";
    infoPortList << "";
    foreach (const QSerialPortInfo &listInfo, serialInfo->availablePorts()) {
        QString dbgString;
        dbgString += "Nome: " + listInfo.portName();
        qDebug() << dbgString;
        infoPortList.push_back(listInfo.portName());
    }

    const QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();
    for (const qint32 baudRate : baudRates) {
        infoBaudList.push_back(QString::number(baudRate));
    }

    return std::make_tuple(infoPortList, infoBaudList);
}

void ComunicacaoSerial::serialWrite(QByteArray data) {
    if (serialDeviceConnected == true) {
        qDebug() << "Enviando: " << data;
        serial->write(data);
        serial->flush();
        qDebug() << "Dados enviados.";
    }
}

void ComunicacaoSerial::serialRead() {
    if (serialDeviceConnected == true) {
        serialBuffer += serial->readAll();
    }
}

void ComunicacaoSerial::serialDataAvalible() {
    if (serialDeviceConnected == true) {
        serialRead();
        qDebug() << "Recebido: " << serialBuffer;
        if (serialBuffer.indexOf("]") != -1) {
            qDebug() << "Messagem do dispositivo: " << serialBuffer;
            serialWrite("echo");
            serialBuffer = "";
        }
    }
}
