#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

// Constructor da classe
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_shared<Ui::MainWindow>()) {
    // Declaração das classes
    comunicaSerial = std::make_shared<ComunicacaoSerial>();
    area = std::make_shared<AreaDeControle>(nullptr, comunicaSerial);

    ui->setupUi(this);

    // Chamada das funções de configuração
    windowConfigs();
    configSerial();
}

// Configurações iniciais da janela
void MainWindow::windowConfigs() {
    this->setFixedSize(538, 260);
    move(screen()->geometry().center() - frameGeometry().center());
}

// Configurações iniciais do QSerialPort
void MainWindow::configSerial() {
    comunicaSerial->serial = new QSerialPort;

    std::tie(portList, baudList) = comunicaSerial->getAvalilableSerialDevice();

    // Adiciona ao ComboBox a lista de Portas USB e os Baud Rate disponíveis
    ui->showPorts->addItems(portList);
    ui->showBauds->addItems(baudList);

    connect(comunicaSerial->serial, &QSerialPort::readyRead,
            comunicaSerial.get(), &ComunicacaoSerial::serialDataAvalible);

    comunicaSerial->serialDeviceConnected = false;
}

// Configuração do aviso de conexão bem sucedida
void MainWindow::buttonStatusOn() {
    ui->statusConnection->setText("Conectado");
    ui->statusColor->setStyleSheet("background-color: #009900;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

// Configuração do aviso de desconexão bem sucedida
void MainWindow::buttonStatusOff() {
    ui->statusConnection->setText("Desconectado");
    ui->statusColor->setStyleSheet("background-color: #FF0000;");
    QRect rect(0, 0, 40, 40);
    QRegion region(rect, QRegion::Ellipse);
    ui->statusColor->setMask(region);
}

// Ação para conectar com o dispositivo
void MainWindow::on_connectDevice_clicked() {
    // Mostra as portas USBs disponíveis
    comunicaSerial->serial->setPortName(
        portList[ui->showPorts->currentIndex()].toUtf8());
    // comunicaSerial->serial->setPortName("/dev/pts/1"); // Porta virtual de
    // testes
    qDebug() << "Se conectando com a porta: "
             << comunicaSerial->serial->portName();

    // Caso tenha escolhido a porta tal, realiza a conexão
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

        // Atualiza o aviso de conexão bem sucedida
        buttonStatusOn();
        // Abre a janela da área de controle
        area->show();

        qDebug() << "Conectado na porta : "
                 << comunicaSerial->serial->portName();
        comunicaSerial->serialDeviceConnected = true;
    } else { // Caso a conexão seja mal sucedida, mostra o erro na caixa de
             // texto
        ui->statusConnection->setText("Erro, nenhum dispositivo conectado!!");
        qDebug() << "Ocorreu um erro ao se conectar a porta "
                 << comunicaSerial->serial->portName();
        qDebug() << "Error: " << comunicaSerial->serial->errorString();
        comunicaSerial->serialDeviceConnected = false;
    }
}

// Ação para desconectar o dispositivo
void MainWindow::on_disconnectDevice_clicked() {
    // Caso tenha um dispositivo conectado, realiza a desconexão do mesmo
    if (comunicaSerial->serialDeviceConnected) {
        comunicaSerial->serial->close();
        comunicaSerial->serialDeviceConnected = false;
        qDebug() << "A porta" << comunicaSerial->serial->portName()
                 << "foi desconectada com sucesso.";
        // Atualiza o aviso de desconexão bem sucedida
        buttonStatusOff();
        // Ao desconectar, fecha a janela da área de controle
        area->close();

    } else { // Se não tiver dispositivo conectado, mostra o erro na caixa de
             // texto
        ui->statusConnection->setText("Erro, nenhum dispositivo conectado!!");
        qDebug() << "Nenhum dispositivo conectado";
    }
}
