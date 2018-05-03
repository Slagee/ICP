#include "Adder.h"

Adder::Adder(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int Adder::getBlockWidth() const { return BLOCK_WIDTH; }

int Adder::getBlockHeight() const { return BLOCK_HEIGHT; }

int Adder::getInPortsCount() const { return IN_PORTS_COUNT; }

int Adder::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int Adder::getBlockType() const { return BLOCK_TYPE; }

QString Adder::getBlockName() const { return BLOCK_NAME; }

QString Adder::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Adder::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Adder::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Adder::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Adder::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
