#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("TIK Lab 1");
    w.setFixedHeight(800);
    w.setFixedWidth(800);
    w.show();

    return a.exec();
}
