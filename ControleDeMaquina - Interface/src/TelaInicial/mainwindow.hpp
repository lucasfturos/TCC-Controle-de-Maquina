#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QScreen>
#include <src/AreaDeControle/areadecontrole.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);

  private slots:
    void on_connectDevice_clicked();
    void on_disconnectDevice_clicked();

  private:
    // Classes
    std::shared_ptr<Ui::MainWindow> ui;
    std::shared_ptr<AreaDeControle> area;
    std::shared_ptr<ComunicacaoSerial> comunicaSerial;

    // Funções
    void windowConfigs();
    void buttonStatusOn();
    void buttonStatusOff();
    void configSerial();

    // Variáveis
    QStringList baudList, portList;
};
#endif // MAINWINDOW_HPP
