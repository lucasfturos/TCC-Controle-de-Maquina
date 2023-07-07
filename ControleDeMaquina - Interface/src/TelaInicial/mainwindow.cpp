#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    comunicaSerial = std::make_shared<ComunicacaoSerial>();
    ui->setupUi(this);
    windowConfigs();
    configSerial();
    configAreaDeControle();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::windowConfigs() {
    this->setFixedSize(538, 260);
    move(screen()->geometry().center() - frameGeometry().center());
}

void MainWindow::configSerial() {
    comunicaSerial->serial = new QSerialPort(this);
    std::tie(portList, baudList) = comunicaSerial->getAvalilableSerialDevice();

    ui->showPorts->addItems(portList);
    ui->showBauds->addItems(baudList);

    connect(comunicaSerial->serial, SIGNAL(comunicaSerial.serial->readyRead()), this,
            SLOT(comunicaSeria.serialRead()));
    connect(ui->connectDevice, SIGNAL(clicked()), this,SLOT(comunicaSerial->serialDataAvalible()));

    comunicaSerial->serialDeviceConnected = false;
}

void MainWindow::configAreaDeControle() {
    area = std::make_shared<AreaDeControle>();
    area->show();
}

void MainWindow::buttonStatusOn() {
    ui->statusConnection->setText("Conectado");
    ui->statusColor->setStyleSheet("background-color: #009900;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

void MainWindow::buttonStatusOff() {
    ui->statusConnection->setText("Desconectado");
    ui->statusColor->setStyleSheet("background-color: #FF0000;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

void MainWindow::on_connectDevice_clicked() {
    comunicaSerial->serial->setPortName(
                portList[ui->showPorts->currentIndex()].toUtf8());
    // comunicaSerial.serial->setPortName("/tmp/ttyUSB0");
    qDebug() << "Se conectando com a porta: "
             << comunicaSerial->serial->portName();

    if (comunicaSerial->serial->open(QIODevice::ReadWrite)) {
        if (!comunicaSerial->serial->setBaudRate(
                    baudList[ui->showBauds->currentIndex()].toInt())) {
            qDebug() << "Conectado com taxa de transmissão de "
                     << baudList[ui->showBauds->currentIndex()].toInt();
            qDebug() << comunicaSerial->serial->errorString();
        }
        if (!comunicaSerial->serial->setDataBits(QSerialPort::Data8)) {
            qDebug() << comunicaSerial->serial->errorString();
        }
        if (!comunicaSerial->serial->setParity(QSerialPort::NoParity)) {
            qDebug() << comunicaSerial->serial->errorString();
        }
        if (!comunicaSerial->serial->setStopBits(QSerialPort::OneStop)) {
            qDebug() << comunicaSerial->serial->errorString();
        }
        if (!comunicaSerial->serial->setFlowControl(
                    QSerialPort::NoFlowControl)) {
            qDebug() << comunicaSerial->serial->errorString();
        }

        buttonStatusOn();
        qDebug() << "Conectado na porta : "
                 << comunicaSerial->serial->portName();
        comunicaSerial->serialDeviceConnected = true;
    } else {
        ui->statusConnection->setText("Erro, nenhum dispositivo conectado!!");
        qDebug() << "Ocorreu um erro ao se conectar a porta "
                 << comunicaSerial->serial->portName();
        qDebug() << "Error: " << comunicaSerial->serial->errorString();
        comunicaSerial->serialDeviceConnected = false;
    }
}

void MainWindow::on_disconnectDevice_clicked() {
    if (comunicaSerial->serialDeviceConnected) {
        comunicaSerial->serial->close();
        comunicaSerial->serialDeviceConnected = false;
        qDebug() << "A porta" << comunicaSerial->serial->portName()
                 << "foi desconectada com sucesso.";
        buttonStatusOff();

    } else {
        ui->statusConnection->setText("Erro, nenhum dispositivo conectado!!");
        qDebug() << "Nenhum dispositivo conectado";
    }
}
