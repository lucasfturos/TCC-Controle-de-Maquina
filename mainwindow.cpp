#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectPort_clicked()
{
    ui->statusConnection->setText("Conectado");
    ui->connectPort->setDisabled(true);
    ui->disconnectPort->setEnabled(true);
}


void MainWindow::on_disconnectPort_clicked()
{
    ui->statusConnection->setText("Desconectado");
    ui->connectPort->setEnabled(true);
    ui->disconnectPort->setDisabled(true);
}
