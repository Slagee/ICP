#include "adder1w1a2w1to1w1a2w2a3w3.h"

adder1w1a2w1to1w1a2w2a3w3::adder1w1a2w1to1w1a2w2a3w3(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int adder1w1a2w1to1w1a2w2a3w3::getBlockWidth() const { return BLOCK_WIDTH; }

int adder1w1a2w1to1w1a2w2a3w3::getBlockHeight() const { return BLOCK_HEIGHT; }

int adder1w1a2w1to1w1a2w2a3w3::getInPortsCount() const { return IN_PORTS_COUNT; }

int adder1w1a2w1to1w1a2w2a3w3::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString adder1w1a2w1to1w1a2w2a3w3::getBlockName() const { return BLOCK_NAME; }

QString adder1w1a2w1to1w1a2w2a3w3::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString adder1w1a2w1to1w1a2w2a3w3::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString adder1w1a2w1to1w1a2w2a3w3::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString adder1w1a2w1to1w1a2w2a3w3::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void adder1w1a2w1to1w1a2w2a3w3::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
    this->getOutPort(1)->getDataType()->setValue(0, result);
    this->getOutPort(1)->getDataType()->setValue(1, result);
    this->getOutPort(2)->getDataType()->setValue(0, result);
    this->getOutPort(2)->getDataType()->setValue(1, result);
    this->getOutPort(2)->getDataType()->setValue(2, result);
}
