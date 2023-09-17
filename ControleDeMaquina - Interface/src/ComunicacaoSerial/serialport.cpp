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

void ComunicacaoSerial::serialWrite(QString data) {
    if (serialDeviceConnected == true) {
        qDebug() << "Enviando: " << data;
        serial->write(data.toUtf8());
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
        int endIndex = serialBuffer.indexOf('\n'); // Encontre o fim da mensagem
        if (endIndex != -1) {
            QString mensagem = serialBuffer.left(endIndex); // Extrai a mensagem
            qDebug() << "Mensagem do dispositivo: " << mensagem;
            serialWrite("echo"); // Envie uma resposta
            serialBuffer =
                    serialBuffer.mid(endIndex + 1); // Remove a mensagem do buffer
        }
        serialBuffer.clear();
    }
}
