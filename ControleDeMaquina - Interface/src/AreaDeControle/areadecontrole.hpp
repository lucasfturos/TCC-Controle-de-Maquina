#ifndef AREADECONTROLE_HPP
#define AREADECONTROLE_HPP

#include <QList>
#include <memory>
#include <QDebug>
#include <QScreen>
#include <QTextEdit>
#include <QMainWindow>
#include <src/ComunicacaoSerial/serialport.hpp>

namespace Ui {
class AreaDeControle;
}

class AreaDeControle : public QMainWindow {
    Q_OBJECT

public:
    explicit AreaDeControle(QWidget *parent = nullptr);
    ~AreaDeControle();

private slots:

private slots:
    void on_buttonLed_clicked();
    void on_enviarDisplayLCD_clicked();
    void on_buttonMotorPasso_clicked();
    void on_buttonMotorEletric_clicked();

private:
    void setupLed();
    void setupDisplayLCD();
    void setupMotorPasso();
    void setupMotorEletrico();

    Ui::AreaDeControle *ui;
    std::shared_ptr<ComunicacaoSerial> serial;

    QList<QString> mensagemPreProgramadas;
    QList<QString> infoEstadoValvula;
    bool stateButtonLed;
    bool stateButtonMotorPasso;
    bool stateButtonMotorEletrico;

};

#endif // AREADECONTROLE_HPP
