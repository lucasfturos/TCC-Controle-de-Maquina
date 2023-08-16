#include "TelaInicial/mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    auto a = std::make_shared<QApplication>(argc, argv);
    auto w = std::make_shared<MainWindow>();
    w->show();
    return a->exec();
}
