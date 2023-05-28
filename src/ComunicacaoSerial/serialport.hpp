#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP

#include <QFile>
#include <tuple>
#include <QDebug>
#include <QTextStream>
#include <QSerialPort>
#include <QSerialPortInfo>

class ComunicacaoSerial : public QObject{
    Q_OBJECT
public:
    std::tuple<QStringList, QStringList> getAvalilableSerialDevice();
    QSerialPort *serial;
    bool serialDeviceConnected;
    void logData(QByteArray &data);
    void serialWrite(QByteArray &data);

public slots:
    void serialDataAvalible();
    void serialRead();

private:
    QSerialPortInfo *serialInfo;
    QStringList infoBaudList;
    QStringList infoPortList;
    QString serialBuffer;

};

#endif // SERIALPORT_HPP
