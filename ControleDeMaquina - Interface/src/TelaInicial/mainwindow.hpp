#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <src/AreaDeControle/areadecontrole.hpp>
#include <src/ComunicacaoSerial/serialport.hpp>
#include <QMainWindow>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_connectDevice_clicked();
    void on_disconnectDevice_clicked();

  private:
    Ui::MainWindow *ui;
    AreaDeControle *area;
    MainWindow *buscar;
    ComunicacaoSerial comunicaSerial;

    void windowConfigs();
    void buttonStatusOn();
    void buttonStatusOff();
    void configSerial();
    void configAreaDeControle();

    QStringList baudList, portList;
};
#endif // MAINWINDOW_HPP
