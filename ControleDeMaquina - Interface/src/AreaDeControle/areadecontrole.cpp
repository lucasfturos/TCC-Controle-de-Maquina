#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

// Constructor da classe
AreaDeControle::AreaDeControle(QWidget *parent,
                               std::shared_ptr<ComunicacaoSerial> connectSerial)
    : QMainWindow(parent), ui(std::make_shared<Ui::AreaDeControle>()),
      serialConnection(connectSerial) {
    ui->setupUi(this);
    // Configurações da janela
    this->setFixedSize(670, 420);
    move(screen()->geometry().center() - frameGeometry().center());

    // Configuração dos componentes da interface
    setupLed();
    setupDisplayLCD();
    setupMotorPasso();
    setupMotorEletrico();
}

// Configurações iniciais do botão do motor DC
void AreaDeControle::setupMotorEletrico() {
    stateButtonMotorEletrico = false;
    ui->buttonMotorEletric->setText("Ligar");
}

// Configurações iniciais do botão da Luz de aviso
void AreaDeControle::setupLed() {
    stateButtonLed = false;
    ui->buttonLed->setText("Ligar");
}

// Configurações iniciais do ComboBox e caixa de texto das mensagens do Display
// LCD
void AreaDeControle::setupDisplayLCD() {
    mensagemPreProgramadas = {
        "Mensagens Pré-Programadas", "Problema: motor parou",
        "Problema: valvula",         "Aviso: saida imediata",
        "Aviso: incendio",           "Aviso: Gas vazando",
    };

    // ComboBox
    ui->mensagemDisplayLCD->addItems(mensagemPreProgramadas);

    // TextEdit
    ui->textEditDisplayLcd->setPlaceholderText("Informe a mensagem.");
}

// Configurações iniciais do ComboBox dos estados da Valvula
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

// Ações do botão do LED
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

// Ações do botão do Motor DC
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

// Ações do botão do Display LCD
void AreaDeControle::on_enviarDisplayLCD_clicked() {
    QString mensagem = ui->textEditDisplayLcd->toPlainText();
    QString mgProgramada = ui->mensagemDisplayLCD->currentText();

    // Caso a caixa de texto esteja preenchido manda a mensagem
    if (!mensagem.isEmpty()) {
        QString data = "!" + mensagem + ";";
        serialConnection->serialWrite(data.toUtf8());
    }

    // Caso a mensagem pré-programada esteja selecionada, manda o comando
    int selectedIdx = ui->mensagemDisplayLCD->currentIndex();
    if (selectedIdx > 0) {
        QString datapg = "!" + mgProgramada + ";";
        serialConnection->serialWrite(datapg.toUtf8());
    }
}

// Ações do motor de passo
void AreaDeControle::on_buttonMotorPasso_clicked() {
    int selectedIdx = ui->estadoValvula->currentIndex();

    // Caso o ComboBox seja selecionado realiza a ação
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

        // Caso for selecionado uma das opções manda o comando
        if (numCommands > 0) {
            // Comando de girar para esquerda ou direita para realizar a
            // abertura ou fechamento da válvula
            QString command = (stateButtonMotorPasso) ? "SL\n" : "SR\n";

            // Manda o comando
            for (int i = 0; i < numCommands; ++i) {
                serialConnection->serialWrite(command.toUtf8());
            }

            stateButtonMotorPasso = !stateButtonMotorPasso;
            // Muda o label do botão
            ui->buttonMotorPasso->setText((stateButtonMotorPasso) ? "Ligar"
                                                                  : "Desligar");
        }
    }
}
