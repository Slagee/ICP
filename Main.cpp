/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "MainWindow.h"
#include <QApplication>

/*!
 * \brief Hlavní funkce programu.
 * \param argc - počet argumentů programu
 * \param argv - ukazatel na argumenty programu
 * \return Vrací návratový kód programu.
 */
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow window;

    window.setFixedSize(1280, 720);
    window.show();

    return a.exec();
}
