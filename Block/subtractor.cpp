#include "subtractor.h"

subtractor::subtractor(int x, int y, QGraphicsScene *parent) {
    startX = x - BLOCK_WIDTH / 2;
    startY = y - BLOCK_HEIGHT / 2;
    myParent = parent;

    setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    constructBlock();
}

int subtractor::getBlockWidth() const { return BLOCK_WIDTH; }

int subtractor::getBlockHeight() const { return BLOCK_HEIGHT; }

int subtractor::getInPortsCount() const { return IN_PORTS_COUNT; }

int subtractor::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString subtractor::getBlockName() const { return BLOCK_NAME; }
