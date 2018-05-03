#include "Multiplier.h"

Multiplier::Multiplier(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int Multiplier::getBlockWidth() const { return BLOCK_WIDTH; }

int Multiplier::getBlockHeight() const { return BLOCK_HEIGHT; }

int Multiplier::getInPortsCount() const { return IN_PORTS_COUNT; }

int Multiplier::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int Multiplier::getBlockType() const { return BLOCK_TYPE; }

QString Multiplier::getBlockName() const { return BLOCK_NAME; }

QString Multiplier::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Multiplier::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Multiplier::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Multiplier::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Multiplier::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) * this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
