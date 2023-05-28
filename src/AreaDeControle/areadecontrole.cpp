#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AreaDeControle) {
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());

    ui->sliderMotorPasso->setValue(180);
    textEditMotorPasso();
    ui->textEditMotorPasso->setLineWrapColumnOrWidth(3);

    stateButtonLed = stateButtonMotorEletrico = false;
    ui->buttonLed->setText("Ligar");
    ui->buttonMotorEletric->setText("Ligar");

    connect(ui->sliderMotorPasso, &QSlider::valueChanged, this, &AreaDeControle::textEditMotorPasso);
    connect(ui->textEditMotorPasso, SIGNAL(textChanged()), this, SLOT(on_textEditMotorPasso_textChanged()));
}

AreaDeControle::~AreaDeControle() { delete ui; }

void AreaDeControle::textEditMotorPasso() {
    ui->textEditMotorPasso->setText(
                QString::number(ui->sliderMotorPasso->value()));
}

void AreaDeControle::on_buttonLed_clicked() {
    QByteArray led1 = "1", led0 = "0";
    if (stateButtonLed) {
        ui->buttonLed->setText("Ligar");
        serial->serialWrite(led0);
    } else {
        ui->buttonLed->setText("Desligar");
        serial->serialWrite(led1);
    }
}

void AreaDeControle::on_textEditMotorPasso_textChanged() {
    QString text = ui->textEditMotorPasso->toPlainText();
    qint8 maxLength = 3;

    if (text.length() > maxLength) {
        ui->textEditMotorPasso->setPlainText(text.left(maxLength));
    }
}

void AreaDeControle::on_buttonMotorEletric_clicked()
{
    QByteArray motor1 = "1", motor0 = "0";
    if (stateButtonMotorEletrico) {
        ui->buttonMotorEletric->setText("Ligar");
        serial->serialWrite(motor0);
    } else {
        ui->buttonMotorEletric->setText("Desligar");
        serial->serialWrite(motor1);
    }
}
