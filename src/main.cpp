#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication carService(argc, argv);
    carService.setStyle("fusion");
    MainWindow mainwindow(&carService);
    mainwindow.show();
    return carService.exec();
}
