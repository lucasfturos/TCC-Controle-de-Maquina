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

void ComunicacaoSerial::serialWrite(QByteArray &data) {
    if (serialDeviceConnected == true) {
        serial->write(data);
        qDebug() << "Dados enviados para o dispositivo: " << data;
    }
}

void ComunicacaoSerial::serialRead() {
    if (serialDeviceConnected == true) {
        serialBuffer.clear();
        serialBuffer += serial->readAll();
    }
}

void ComunicacaoSerial::serialDataAvalible() {
    QByteArray data_message = "echoPIC";

    if (serialDeviceConnected == true) {
        serialRead();
        if (serialBuffer.indexOf("]") != -1) {
            qDebug() << "Messagem do dispositivo: " << serialBuffer;
            serialWrite(data_message);
            serialBuffer = "";
        }
    }
}
