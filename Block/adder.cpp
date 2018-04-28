#include "adder.h"

adder::adder(int x, int y, QGraphicsScene *parent) {
    pressed = false;
    startX = x - BLOCK_WIDTH / 2;
    startY = y - BLOCK_HEIGHT / 2;
    myParent = parent;

    setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    constructBlock();
}

int adder::getBlockWidth() const { return BLOCK_WIDTH; }

int adder::getBlockHeight() const { return BLOCK_HEIGHT; }

int adder::getInPortsCount() const { return IN_PORTS_COUNT; }

int adder::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString adder::getBlockName() const { return BLOCK_NAME; }
