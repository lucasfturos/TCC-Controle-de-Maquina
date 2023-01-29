#include "areadecontrole.hpp"
#include "ui_areadecontrole.h"

AreaDeControle::AreaDeControle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AreaDeControle)
{
    ui->setupUi(this);
}

AreaDeControle::~AreaDeControle()
{
    delete ui;
}
