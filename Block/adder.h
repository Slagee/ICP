#ifndef ADDER_H
#define ADDER_H

#include "abstractblock.h"

class adder : public abstractblock {
private:
    const int BLOCK_WIDTH = 100;
    const int BLOCK_HEIGHT = 40;
    const int IN_PORTS_COUNT = 3;
    const int OUT_PORTS_COUNT = 1;
    const QString BLOCK_NAME = "ADDER";

public:
    adder(qreal x, qreal y);
    int getBlockWidth() const;
    int getBlockHeight() const;
    int getInPortsCount() const;
    int getOutPortsCount() const;
};

#endif // ADDER_H
