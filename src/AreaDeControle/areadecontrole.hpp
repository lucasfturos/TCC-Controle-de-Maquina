#ifndef AREADECONTROLE_HPP
#define AREADECONTROLE_HPP

#include <QMainWindow>
#include <QScreen>

namespace Ui {
class AreaDeControle;
}

class AreaDeControle : public QMainWindow
{
    Q_OBJECT

public:
    explicit AreaDeControle(QWidget *parent = nullptr);
    ~AreaDeControle();

private slots:
    void textEditMotorPasso();

private:
    Ui::AreaDeControle *ui;
};

#endif // AREADECONTROLE_HPP
