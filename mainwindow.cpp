#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "serialport.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial->serialConecta();
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->~SerialPort();
}


void MainWindow::on_connectPort_clicked()
{
    home = new homedevice(this);
    MainWindow main;
    ui->statusConnection->setText("Conectado");
    ui->connectPort->setDisabled(true);
    ui->disconnectPort->setEnabled(true);
    home->show();
}


void MainWindow::on_disconnectPort_clicked()
{
    ui->statusConnection->setText("Desconectado");
    ui->connectPort->setEnabled(true);
    ui->disconnectPort->setDisabled(true);
}


void MainWindow::on_searchDevice_clicked()
{
    // ui->showMessage->setEditText(serial->readAll());
}
