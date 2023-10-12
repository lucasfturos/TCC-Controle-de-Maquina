#include "serialport.hpp"

// Função que pega a porta e baud rate disponiveis
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

// Função que habilita a escrita para a porta serial
void ComunicacaoSerial::serialWrite(QByteArray data) {
    if (serialDeviceConnected == true) {
        qDebug() << "Enviando: " << data;
        // Manda a escrita para o dispositivo
        serial->write(data);
        serial->flush();
        qDebug() << "Dados enviados.";
    }
}

// Função que habilita a leitura da porta serial
void ComunicacaoSerial::serialRead() {
    if (serialDeviceConnected == true) {
        // Lê as respostas do dispositivo
        serialBuffer += serial->readAll();
    }
}

// Mostra as respostas de leitura e escrita do dispositivo
void ComunicacaoSerial::serialDataAvalible() {
    if (serialDeviceConnected == true) {
        // Mostra as mensagens de leitura
        serialRead();
        qDebug() << "Recebido: " << serialBuffer;
        if (serialBuffer.indexOf("]") != -1) {
            qDebug() << "Messagem do dispositivo: " << serialBuffer;
            // Manda um aviso para confirmar a resposta do dispositivo
            serialWrite("echo");
            serialBuffer = "";
        }
    }
}
