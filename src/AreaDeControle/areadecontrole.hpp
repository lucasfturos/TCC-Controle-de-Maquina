#ifndef AREADECONTROLE_HPP
#define AREADECONTROLE_HPP

#include <QMainWindow>
#include <QScreen>
#include <QList>
#include <QSlider>
#include <QTextEdit>
#include "../ComunicacaoSerial/serialport.hpp"

namespace Ui {
class AreaDeControle;
}

class AreaDeControle : public QMainWindow {
    Q_OBJECT

  public:
    explicit AreaDeControle(QWidget *parent = nullptr);
    ~AreaDeControle();

  private slots:
    void textEditMotorPasso();
    void on_buttonLed_clicked();
    void on_textEditMotorPasso_textChanged();
    void on_buttonMotorEletric_clicked();

private:
    Ui::AreaDeControle *ui;
    ComunicacaoSerial *serial;

    bool stateButtonLed;
    bool stateButtonMotorEletrico;
};

#endif // AREADECONTROLE_HPP
