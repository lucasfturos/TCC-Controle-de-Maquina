#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AreaDeControle) {
    ui->setupUi(this);
    this->setFixedSize(670, 420);
    move(screen()->geometry().center() - frameGeometry().center());

    // Configuração dos componentes da interface
    setupLed();
    setupDisplayLCD();
    setupMotorPasso();
    setupMotorEletrico();
}

AreaDeControle::~AreaDeControle() { delete ui; }

void AreaDeControle::setupMotorEletrico() {
    stateButtonMotorEletrico = false;
    ui->buttonMotorEletric->setText("Ligar");
}

void AreaDeControle::setupLed() {
    stateButtonLed = false;
    ui->buttonLed->setText("Ligar");
}

void AreaDeControle::setupDisplayLCD() {
    mensagemPreProgramadas = {"Mensagens Pré-Programadas", "Motor 1: Ligado",
                              "Motor 1: Desligado",        "Valvula 1: Ligado",
                              "Valvula 2: Desligado",      "LED 1: Ligado",
                              "LED 2: Desligado"};
    ui->textEditDisplayLcd->setPlaceholderText("Informe a mensagem.");
    ui->mensagemDisplayLCD->addItems(mensagemPreProgramadas);
}

void AreaDeControle::setupMotorPasso(){
    ui->buttonMotorPasso->setText("Ligar");
    stateButtonMotorPasso = false;
    infoEstadoValvula = {"Estado de Abertuda da Valvula", "Baixa", "Média", "Alta"};
    ui->estadoValvula->addItems(infoEstadoValvula);
    ui->testeMotorPasso->setPlaceholderText("Informe um ângulo para o teste");
}

void AreaDeControle::on_buttonLed_clicked() {
    QByteArray led1 = "1", led0 = "0";
    if (stateButtonLed) {
        ui->buttonLed->setText("Ligar");
        stateButtonLed = false;
        // serial->serialWrite(led1);
    } else {
        ui->buttonLed->setText("Desligar");
        stateButtonLed = true;
        // serial->serialWrite(led0);
    }
}

void AreaDeControle::on_buttonMotorEletric_clicked() {
    QByteArray motor1 = "A", motor0 = "B";
    if (stateButtonMotorEletrico) {
        ui->buttonMotorEletric->setText("Ligar");
        stateButtonMotorEletrico = false;
        // serial->serialWrite(motor0);
    } else {
        ui->buttonMotorEletric->setText("Desligar");
        stateButtonMotorEletrico = true;
        // serial->serialWrite(motor1);
    }
}

void AreaDeControle::on_enviarDisplayLCD_clicked()
{
    // Enviar mensagens
}

void AreaDeControle::on_buttonMotorPasso_clicked()
{
    QByteArray angulo = "90", estato = "baixo", desligar = "C";
    if (stateButtonMotorPasso) {
        ui->buttonMotorPasso->setText("Ligar");
        stateButtonMotorPasso = false;
        // serial->serialWrite(angulo);
    } else {
        ui->buttonMotorPasso->setText("Desligar");
        stateButtonMotorPasso = true;
        // serial->serialWrite(desligar);
    }
}
