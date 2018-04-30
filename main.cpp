#include "mainwindow.h"
#include <QApplication>

// hlavni funkce programu
int main(int argc, char *argv[]) {

    // aplikace...
    QApplication a(argc, argv);

    // okno...
    MainWindow w;

    w.setFixedSize(1280, 720);
    w.show();

    return a.exec();
}
