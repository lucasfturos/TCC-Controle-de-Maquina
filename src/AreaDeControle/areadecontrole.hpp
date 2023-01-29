#ifndef AREADECONTROLE_HPP
#define AREADECONTROLE_HPP

#include <QMainWindow>

namespace Ui {
class AreaDeControle;
}

class AreaDeControle : public QMainWindow
{
    Q_OBJECT

public:
    explicit AreaDeControle(QWidget *parent = nullptr);
    ~AreaDeControle();

private:
    Ui::AreaDeControle *ui;
};

#endif // AREADECONTROLE_HPP
