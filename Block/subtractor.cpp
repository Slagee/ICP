#include "subtractor.h"

subtractor::subtractor(qreal x, qreal y) {
    pressed = false;
    startX = x;
    startY = y;

    setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);

    constructBlock();
}

int subtractor::getBlockWidth() const { return BLOCK_WIDTH; }

int subtractor::getBlockHeight() const { return BLOCK_HEIGHT; }

int subtractor::getInPortsCount() const { return IN_PORTS_COUNT; }

int subtractor::getOutPortsCount() const { return OUT_PORTS_COUNT; }
