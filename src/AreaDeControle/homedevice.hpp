#ifndef HOMEDEVICE_HPP
#define HOMEDEVICE_HPP

#include <QObject>
#include <QtQml>

class homedevice : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit homedevice(QObject *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:

};

#endif // HOMEDEVICE_HPP
