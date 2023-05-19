#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <tuple>

class ComunicacaoSerial {
  public:
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();
    QSerialPort *serial;
    bool serialDeviceConnected;
  public slots:
    void serialDataAvalible();
    void serialRead();

  private:
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList;
    QStringList infoPortList;
    QString serialBuffer;

    void serialWrite(QString message);
};

#endif // SERIALPORT_HPP
