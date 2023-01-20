#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "homedevice.hpp"
#include "serialport.hpp"

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
    void on_connectPort_clicked();
    void on_disconnectPort_clicked();
    void on_searchDevice_clicked();


private:
    Ui::MainWindow *ui;
    homedevice *home;
    MainWindow *buscar;
    SerialPort *serial;
};
#endif // MAINWINDOW_HPP