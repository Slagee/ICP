#include "MainWindow.h"
#include <QApplication>

// hlavni funkce programu
int main(int argc, char *argv[]) {

    // aplikace...
    QApplication a(argc, argv);

    // okno...
    MainWindow window;

    window.setFixedSize(1280, 720);
    window.show();

    return a.exec();
}
