#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent,
                               std::shared_ptr<ComunicacaoSerial> connectSerial)
    : QMainWindow(parent), ui(std::make_shared<Ui::AreaDeControle>()),
      serialConnection(connectSerial) {
    ui->setupUi(this);
    this->setFixedSize(670, 420);
    move(screen()->geometry().center() - frameGeometry().center());

    // Configuração dos componentes da interface
    setupLed();
    setupDisplayLCD();
    setupMotorPasso();
    setupMotorEletrico();
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
    mensagemPreProgramadas = {
        "Mensagens Pré-Programadas", "Problema: motor explodiu",
        "Problema: valvula",         "Aviso: saida imediata",
        "Aviso: incendio",           "Aviso: Gas vazando",
    };

    // ComboBox
    ui->mensagemDisplayLCD->addItems(mensagemPreProgramadas);

    // TextEdit
    ui->textEditDisplayLcd->setPlaceholderText("Informe a mensagem.");
}

void AreaDeControle::setupMotorPasso() {
    ui->buttonMotorPasso->setText("Ligar");
    stateButtonMotorPasso = false;
    infoEstadoValvula = {
        "Estado de Abertuda da Valvula",
        "Baixa",
        "Média",
        "Alta",
    };

    // ComboBox
    ui->estadoValvula->addItems(infoEstadoValvula);
}

void AreaDeControle::on_buttonLed_clicked() {
    QString led1 = "11";
    QString led0 = "10";

    if (stateButtonLed) {
        ui->buttonLed->setText("Ligar");
        stateButtonLed = false;
        serialConnection->serialWrite(led0.toUtf8());
    } else {
        ui->buttonLed->setText("Desligar");
        stateButtonLed = true;
        serialConnection->serialWrite(led1.toUtf8());
    }
}

void AreaDeControle::on_buttonMotorEletric_clicked() {
    QString motor1 = "MD", motor0 = "MC";
    if (stateButtonMotorEletrico) {
        ui->buttonMotorEletric->setText("Ligar");
        stateButtonMotorEletrico = false;
        serialConnection->serialWrite(motor0.toUtf8());
    } else {
        ui->buttonMotorEletric->setText("Desligar");
        stateButtonMotorEletrico = true;
        serialConnection->serialWrite(motor1.toUtf8());
    }
}

void AreaDeControle::on_enviarDisplayLCD_clicked() {
    QString mensagem = ui->textEditDisplayLcd->toPlainText();
    QString mgProgramada = ui->mensagemDisplayLCD->currentText();

    if (!mensagem.isEmpty()) {
        QString data = "!" + mensagem + ";";
        serialConnection->serialWrite(data.toUtf8());
    }

    int selectedIdx = ui->mensagemDisplayLCD->currentIndex();
    if (selectedIdx > 0) {
        QString datapg = "!" + mgProgramada + ";";
        serialConnection->serialWrite(datapg.toUtf8());
    }
}

void AreaDeControle::on_buttonMotorPasso_clicked() {
    int selectedIdx = ui->estadoValvula->currentIndex();

    if (selectedIdx >= 1 && selectedIdx <= 3) {
        int numCommands = 0;

        // Mapeia o índice selecionado para o número de comandos
        switch (selectedIdx) {
        case 1:
            numCommands = 90;
            break;
        case 2:
            numCommands = 180;
            break;
        case 3:
            numCommands = 360;
            break;
        default:
            break;
        }

        if (numCommands > 0) {
            QString command = (stateButtonMotorPasso) ? "SL\n" : "SR\n";

            for (int i = 0; i < numCommands; ++i) {
                serialConnection->serialWrite(command.toUtf8());
            }

            stateButtonMotorPasso = !stateButtonMotorPasso;
            ui->buttonMotorPasso->setText((stateButtonMotorPasso) ? "Ligar"
                                                                  : "Desligar");
        }
    }
}
