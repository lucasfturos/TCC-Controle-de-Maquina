#ifndef HOMEDEVICE_HPP
#define HOMEDEVICE_HPP

#include "src/TelaInicial/mainwindow.hpp"
#include <QObject>

class homedevice : public QObject
{
    Q_OBJECT
//    QML_ELEMENT

public:
    explicit homedevice(QObject *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:

};

#endif // HOMEDEVICE_HPP
