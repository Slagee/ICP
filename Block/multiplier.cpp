#include "multiplier.h"

multiplier::multiplier(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int multiplier::getBlockWidth() const { return BLOCK_WIDTH; }

int multiplier::getBlockHeight() const { return BLOCK_HEIGHT; }

int multiplier::getInPortsCount() const { return IN_PORTS_COUNT; }

int multiplier::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int multiplier::getBlockType() const { return BLOCK_TYPE; }

QString multiplier::getBlockName() const { return BLOCK_NAME; }

QString multiplier::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString multiplier::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString multiplier::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString multiplier::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void multiplier::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) * this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
