#ifndef HOMEDEVICE_HPP
#define HOMEDEVICE_HPP

#include <QDialog>

namespace Ui {
class homedevice;
}

class homedevice : public QDialog
{
    Q_OBJECT

public:
    explicit homedevice(QWidget *parent = nullptr);
    ~homedevice();

private slots:
    void on_pushButton_clicked();

private:
    Ui::homedevice *ui;
};

#endif // HOMEDEVICE_HPP
