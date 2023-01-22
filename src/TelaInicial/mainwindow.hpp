#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "src/AreaDeControle/homedevice.hpp"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

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
    void connectSerialPort();

private:
    Ui::MainWindow *ui;
    homedevice *home;
    MainWindow *buscar;
    QSerialPort *serial;
};
#endif // MAINWINDOW_HPP
