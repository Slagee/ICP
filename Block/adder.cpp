#include "adder.h"

adder::adder(qreal x, qreal y) {
    pressed = false;
    startX = x;
    startY = y;

    setFlag(ItemIsMovable);
}

int adder::getBlockWidth() const { return BLOCK_WIDTH; }

int adder::getBlockHeight() const { return BLOCK_HEIGHT; }

int adder::getInPortsCount() const { return IN_PORTS_COUNT; }

int adder::getOutPortsCount() const { return OUT_PORTS_COUNT; }
