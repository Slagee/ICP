#include "adder1w1a2w2a3w3to1w1a2w1.h"

adder1w1a2w2a3w3to1w1a2w1::adder1w1a2w2a3w3to1w1a2w1(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int adder1w1a2w2a3w3to1w1a2w1::getBlockWidth() const { return BLOCK_WIDTH; }

int adder1w1a2w2a3w3to1w1a2w1::getBlockHeight() const { return BLOCK_HEIGHT; }

int adder1w1a2w2a3w3to1w1a2w1::getInPortsCount() const { return IN_PORTS_COUNT; }

int adder1w1a2w2a3w3to1w1a2w1::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int adder1w1a2w2a3w3to1w1a2w1::getBlockType() const { return BLOCK_TYPE; }

QString adder1w1a2w2a3w3to1w1a2w1::getBlockName() const { return BLOCK_NAME; }

QString adder1w1a2w2a3w3to1w1a2w1::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString adder1w1a2w2a3w3to1w1a2w1::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString adder1w1a2w2a3w3to1w1a2w1::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString adder1w1a2w2a3w3to1w1a2w1::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void adder1w1a2w2a3w3to1w1a2w1::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(1)->getDataType()->getValue(0)  + this->getInPort(1)->getDataType()->getValue(1) + this->getInPort(2)->getDataType()->getValue(0) + this->getInPort(2)->getDataType()->getValue(1) + this->getInPort(2)->getDataType()->getValue(2);
    this->getOutPort(0)->getDataType()->setValue(0, result);
    this->getOutPort(1)->getDataType()->setValue(0, result);
}
