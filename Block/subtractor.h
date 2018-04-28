#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H

#include "abstractBlock.h"

class subtractor : public abstractBlock {
private:
    const int BLOCK_WIDTH = 120;
    const int BLOCK_HEIGHT = 50;
    const int IN_PORTS_COUNT = 2;
    const int OUT_PORTS_COUNT = 1;
    const QString BLOCK_NAME = "SUBTRACTOR";

public:
    subtractor(int x, int y, QGraphicsScene *parent = 0);
    int getBlockWidth() const;
    int getBlockHeight() const;
    int getInPortsCount() const;
    int getOutPortsCount() const;
    QString getBlockName() const;
};

#endif // SUBTRACTOR_H
