#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->serial = new QSerialPort;
    std::size_t i = 0;
    QStringList ports;
    QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, infoList){
        ports.insert(i, info.portName());
        qDebug()<< "Nome: " << info.portName();
        i++;
    }
    ui->showPorts->insertItems(0,ports);
    QStringList bauds;
    bauds << "2400" << "9600" << "19200" << "38400" << "57600" << "115200";
    ui->showBauds->insertItems(0,bauds);
    connect(ui->connectPort, SIGNAL(clicked(bool)), this, SLOT(connectSerialPort()));
    qDebug()<<serial->errorString();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectSerialPort()
{
    home = new homedevice(this);
    if(this->serial->isOpen()){
        this->serial->close();
        ui->statusConnection->setText("Desconectado");
        ui->connectPort->setText("Conectar");
        return;
    }
    this->serial->setPortName(ui->showPorts->currentText());
    this->serial->setBaudRate(ui->showBauds->currentText().toInt());
    if (!this->serial->open(QIODevice::ReadOnly)){
        ui->statusConnection->setText("Erro na conexão");
        return;
    }
    ui->statusConnection->setText("Conectado");
    ui->connectPort->setText("Desconectar");
    home->show();
    qDebug()<<serial->errorString();
}
