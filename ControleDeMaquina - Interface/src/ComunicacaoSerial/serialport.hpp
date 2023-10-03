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
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();
    QSerialPort *serial;
    bool serialDeviceConnected;
    void serialWrite(QByteArray data);

  public slots:
    void serialDataAvalible();
    void serialRead();

  private:
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList;
    QStringList infoPortList;
    QByteArray serialBuffer;
};

#endif // SERIALPORT_HPP
