#include "mainwindow.h"
#include <QApplication>

// hlavni funkce programu
int main(int argc, char *argv[]) {

    // aplikace...
    QApplication a(argc, argv);

    // okno...
    MainWindow w;

    //QDesktopWidget dw;
    //w.setFixedSize(dw.width() * 0.7,dw.height() * 0.7);
    //w.setFixedSize(1280, 720);
    w.show();

    return a.exec();
}
