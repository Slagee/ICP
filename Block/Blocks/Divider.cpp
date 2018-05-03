#include "Divider.h"

Divider::Divider(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int Divider::getBlockWidth() const { return BLOCK_WIDTH; }

int Divider::getBlockHeight() const { return BLOCK_HEIGHT; }

int Divider::getInPortsCount() const { return IN_PORTS_COUNT; }

int Divider::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int Divider::getBlockType() const { return BLOCK_TYPE; }

QString Divider::getBlockName() const { return BLOCK_NAME; }

QString Divider::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Divider::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Divider::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Divider::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Divider::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) / this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
