#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AreaDeControle)
{
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    ui->sliderMotorPasso->setValue(50);
    textEditMotorPasso();
    ui->textEditMotorPasso->setLineWrapColumnOrWidth(3);
}

AreaDeControle::~AreaDeControle()
{
    delete ui;
}

void AreaDeControle::textEditMotorPasso()
{
    ui->textEditMotorPasso->setText(QString::number(ui->sliderMotorPasso->value()));
}
