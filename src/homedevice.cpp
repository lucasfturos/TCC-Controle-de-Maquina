#include "src/includes/homedevice.hpp"
#include "ui_homedevice.h"
#include "src/includes/mainwindow.hpp"

homedevice::homedevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homedevice)
{
    ui->setupUi(this);
}

homedevice::~homedevice()
{
    delete ui;
}

void homedevice::on_pushButton_clicked()
{
    close();
}
