/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

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

QString Adder::getBlockClassName() const { return BLOCK_CLASS_NAME; }

QString Adder::getBlockName() const { return BLOCK_NAME; }

QString Adder::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Adder::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Adder::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Adder::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Adder::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(1)->getDataType()->getValue(0);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
