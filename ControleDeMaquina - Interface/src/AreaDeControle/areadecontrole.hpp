#ifndef AREADECONTROLE_HPP
#define AREADECONTROLE_HPP

#include <QDebug>
#include <QList>
#include <QMainWindow>
#include <QScreen>
#include <QTextEdit>
#include <memory>
#include <cmath>
#include <src/ComunicacaoSerial/serialport.hpp>

namespace Ui {
class AreaDeControle;
}

class AreaDeControle : public QMainWindow {
    Q_OBJECT

  public:
    explicit AreaDeControle(
        QWidget *parent = nullptr,
        std::shared_ptr<ComunicacaoSerial> connectSerial = nullptr);

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

    std::shared_ptr<Ui::AreaDeControle> ui;
    std::shared_ptr<ComunicacaoSerial> serialConnection;

    QList<QString> mensagemPreProgramadas;
    QList<QString> infoEstadoValvula;
    bool stateButtonLed;
    bool stateButtonMotorPasso;
    bool stateButtonMotorEletrico;
};

#endif // AREADECONTROLE_HPP
