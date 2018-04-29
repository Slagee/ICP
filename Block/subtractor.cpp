#include "subtractor.h"

subtractor::subtractor(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int subtractor::getBlockWidth() const { return BLOCK_WIDTH; }

int subtractor::getBlockHeight() const { return BLOCK_HEIGHT; }

int subtractor::getInPortsCount() const { return IN_PORTS_COUNT; }

int subtractor::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString subtractor::getBlockName() const { return BLOCK_NAME; }

QString subtractor::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString subtractor::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }
