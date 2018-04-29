#ifndef ADDER_H
#define ADDER_H

#include "abstractBlock.h"

class abstractBlock;

// trida bloku adder
class adder : public abstractBlock {
private:
    // konstanty pro velikost bloku, pocet in-portu/out-portu, jejich popisy a nazev bloku
    const int BLOCK_WIDTH = 100;
    const int BLOCK_HEIGHT = 65;
    const static int IN_PORTS_COUNT = 3;
    const QString IN_PORTS_LABELS[IN_PORTS_COUNT] = {"1.1", "2.1", "3.1"};
    const static int OUT_PORTS_COUNT = 1;
    const QString OUT_PORTS_LABELS[OUT_PORTS_COUNT] = {"1.1"};
    const QString BLOCK_NAME = "ADDER";

public:
    // metody pro praci s blokem - konstruktor + metody pro ziskani informaci o bloku
    adder(int x, int y, QGraphicsScene *parent = 0);
    int getBlockWidth() const;
    int getBlockHeight() const;
    int getInPortsCount() const;
    int getOutPortsCount() const;
    QString getBlockName() const;
    QString getInPortLabel(int index) const;
    QString getOutPortLabel(int index) const;
    void doCalculation();
};

#endif // ADDER_H
