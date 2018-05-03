#include "Round.h"

Round::Round(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int Round::getBlockWidth() const { return BLOCK_WIDTH; }

int Round::getBlockHeight() const { return BLOCK_HEIGHT; }

int Round::getInPortsCount() const { return IN_PORTS_COUNT; }

int Round::getOutPortsCount() const { return OUT_PORTS_COUNT; }

int Round::getBlockType() const { return BLOCK_TYPE; }

QString Round::getBlockName() const { return BLOCK_NAME; }

QString Round::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Round::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Round::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Round::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Round::doCalculation() {
    double result = qRound(this->getInPort(0)->getDataType()->getValue(0));
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
