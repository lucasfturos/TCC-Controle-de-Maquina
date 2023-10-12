#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <tuple>

class ComunicacaoSerial : public QObject {
    Q_OBJECT
  public:
    // Variáveis
    QSerialPort *serial;
    bool serialDeviceConnected;

    // Funções
    void serialWrite(QByteArray data);
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();

  public slots:
    void serialDataAvalible();
    void serialRead();

  private:
    // Variáveis
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList;
    QStringList infoPortList;
    QByteArray serialBuffer;
};

#endif // SERIALPORT_HPP
