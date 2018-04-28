#ifndef ADDER_H
#define ADDER_H

#include "abstractBlock.h"
class abstractBlock;

class adder : public abstractBlock {

private:
    const int BLOCK_WIDTH = 100;
    const int BLOCK_HEIGHT = 65;
    const int IN_PORTS_COUNT = 3;
    const int OUT_PORTS_COUNT = 1;
    const QString BLOCK_NAME = "ADDER";

public:
    adder(int x, int y, QGraphicsScene *parent = 0);
    int getBlockWidth() const;
    int getBlockHeight() const;
    int getInPortsCount() const;
    int getOutPortsCount() const;
    QString getBlockName() const;
};

#endif // ADDER_H
