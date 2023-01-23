#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "src/AreaDeControle/homedevice.hpp"
#include "src/ComunicacaoSerial/serialport.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectDevice_clicked();
    void on_disconnectDevice_clicked();

private:
    Ui::MainWindow *ui;
    homedevice *home;
    MainWindow *buscar;
    ComunicacaoSerial comunicaSerial;

    QSerialPort *serial;
    QStringList baudList, portList;
    bool serialDeviceConnected;
};
#endif // MAINWINDOW_HPP
