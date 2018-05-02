#include "divider.h"

divider::divider(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int divider::getBlockWidth() const { return BLOCK_WIDTH; }

int divider::getBlockHeight() const { return BLOCK_HEIGHT; }

int divider::getInPortsCount() const { return IN_PORTS_COUNT; }

int divider::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int divider::getBlockType() const { return BLOCK_TYPE; }

QString divider::getBlockName() const { return BLOCK_NAME; }

QString divider::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString divider::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString divider::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString divider::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void divider::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) / this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
