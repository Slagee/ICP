#include "subtractor.h"

subtractor::subtractor(qreal x, qreal y) {
    Pressed = false;
    startX = x;
    startY = y;

    setFlag(ItemIsMovable);
}

int subtractor::getBlockWidth() const { return BLOCK_WIDTH; }

int subtractor::getBlockHeight() const { return BLOCK_HEIGHT; }

int subtractor::getInPortsCount() const { return IN_PORTS_COUNT; }

int subtractor::getOutPortsCount() const { return OUT_PORTS_COUNT; }
