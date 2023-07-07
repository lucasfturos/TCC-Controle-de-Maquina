#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AreaDeControle) {
    serial = std::make_shared<ComunicacaoSerial>();

    ui->setupUi(this);
    this->setFixedSize(670, 420);
    move(screen()->geometry().center() - frameGeometry().center());

    // Configuração dos componentes da interface
    setupLed();
    setupDisplayLCD();
    setupMotorPasso();
    setupMotorEletrico();
}

AreaDeControle::~AreaDeControle(){
    delete ui;
}

void AreaDeControle::setupMotorEletrico() {
    stateButtonMotorEletrico = false;
    ui->buttonMotorEletric->setText("Ligar");
}

void AreaDeControle::setupLed() {
    stateButtonLed = false;
    ui->buttonLed->setText("Ligar");
}

void AreaDeControle::setupDisplayLCD() {
    mensagemPreProgramadas = {"Mensagens Pré-Programadas",
                              "Problemas no Motor 1", "Problemas na Valvula",
                              "Aviso: Saída imediata", "Aviso: Incendio", "Aviso: Gás Vazando"};

    // ComboBox
    ui->mensagemDisplayLCD->addItems(mensagemPreProgramadas);

    // TextEdit
    ui->textEditDisplayLcd->setPlaceholderText("Informe a mensagem.");
}

void AreaDeControle::setupMotorPasso(){
    ui->buttonMotorPasso->setText("Ligar");
    stateButtonMotorPasso = false;
    infoEstadoValvula = {"Estado de Abertuda da Valvula", "Baixa", "Média", "Alta"};

    // ComboBox
    ui->estadoValvula->addItems(infoEstadoValvula);

    // TextEdit
    ui->testeMotorPasso->setPlaceholderText("Informe um ângulo");
}

void AreaDeControle::on_buttonLed_clicked() {
    QByteArray led1 = "1", led0 = "0";
    if (stateButtonLed) {
        ui->buttonLed->setText("Ligar");
        stateButtonLed = false;
        serial->serialWrite(led1);
    } else {
        ui->buttonLed->setText("Desligar");
        stateButtonLed = true;
        serial->serialWrite(led0);
    }
}

void AreaDeControle::on_buttonMotorEletric_clicked() {
    QByteArray motor1 = "A", motor0 = "B";
    if (stateButtonMotorEletrico) {
        ui->buttonMotorEletric->setText("Ligar");
        stateButtonMotorEletrico = false;
        serial->serialWrite(motor0);
    } else {
        ui->buttonMotorEletric->setText("Desligar");
        stateButtonMotorEletrico = true;
        serial->serialWrite(motor1);
    }
}

void AreaDeControle::on_enviarDisplayLCD_clicked()
{
    QString mensagem = ui->mensagemDisplayLCD->currentText();
    QByteArray aux;
    aux += mensagem.toUtf8();
    serial->serialWrite(aux);
}

void AreaDeControle::on_buttonMotorPasso_clicked()
{
    QByteArray angulo = "90", estato = "baixo", desligar = "C";
    if (stateButtonMotorPasso) {
        ui->buttonMotorPasso->setText("Ligar");
        stateButtonMotorPasso = false;
        serial->serialWrite(angulo);
    } else {
        ui->buttonMotorPasso->setText("Desligar");
        stateButtonMotorPasso = true;
        serial->serialWrite(desligar);
    }
}
