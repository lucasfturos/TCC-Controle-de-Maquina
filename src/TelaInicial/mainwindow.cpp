#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windowConfigs();
    configSerial();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial;
}

void MainWindow::windowConfigs()
{
    this->setFixedSize(538,260);
    move(screen()->geometry().center() - frameGeometry().center());
}

void MainWindow::configSerial()
{
    std::tie(portList, baudList) = comunicaSerial.getAvalilableSerialDevice();
    ui->showPorts->insertItems(0, portList);
    ui->showBauds->insertItems(0, baudList);
    connect(serial, SIGNAL(comunicaSerial.serialRead()), this, SLOT(comunicaSerial.serialDataAvalible()));
    serialDeviceConnected = false;
}

void MainWindow::buttonStatusOn()
{
    ui->statusConnection->setText("Conectado");
    ui->statusColor->setStyleSheet("background-color: #009900;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

void MainWindow::buttonStatusOff()
{
    ui->statusConnection->setText("Desconectado");
    ui->statusColor->setStyleSheet("background-color: #FF0000;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

void MainWindow::on_connectDevice_clicked()
{
    buttonStatusOn();
}

void MainWindow::on_disconnectDevice_clicked()
{
    buttonStatusOff();
}
