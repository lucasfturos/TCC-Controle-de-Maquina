#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::tie(portList, baudList) = comunicaSerial.getAvalilableSerialDevice();
    ui->showPorts->insertItems(0, portList);
    ui->showBauds->insertItems(0, baudList);
    connect(serial, SIGNAL(comunicaSerial.serialRead()), this, SLOT(comunicaSerial.serialDataAvalible()));
    serialDeviceConnected = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial;
}

void MainWindow::on_connectDevice_clicked()
{

}

void MainWindow::on_disconnectDevice_clicked()
{

}
