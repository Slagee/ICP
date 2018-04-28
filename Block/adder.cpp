#include "adder.h"

adder::adder(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int adder::getBlockWidth() const { return BLOCK_WIDTH; }

int adder::getBlockHeight() const { return BLOCK_HEIGHT; }

int adder::getInPortsCount() const { return IN_PORTS_COUNT; }

int adder::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString adder::getBlockName() const { return BLOCK_NAME; }

QString adder::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString adder::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }
