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

int adder::getBlockType() const { return BLOCK_TYPE; }

QString adder::getBlockName() const { return BLOCK_NAME; }

QString adder::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString adder::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString adder::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString adder::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void adder::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
