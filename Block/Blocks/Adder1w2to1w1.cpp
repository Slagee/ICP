/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Adder1w2to1w1.h"

Adder1w2to1w1::Adder1w2to1w1(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int Adder1w2to1w1::getBlockWidth() const { return BLOCK_WIDTH; }

int Adder1w2to1w1::getBlockHeight() const { return BLOCK_HEIGHT; }

int Adder1w2to1w1::getInPortsCount() const { return IN_PORTS_COUNT; }

int Adder1w2to1w1::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString Adder1w2to1w1::getBlockClassName() const { return BLOCK_CLASS_NAME; }

QString Adder1w2to1w1::getBlockName() const { return BLOCK_NAME; }

QString Adder1w2to1w1::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString Adder1w2to1w1::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString Adder1w2to1w1::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString Adder1w2to1w1::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void Adder1w2to1w1::doCalculation() {
    double result = this->getInPort(0)->getDataType()->getValue(0) + this->getInPort(0)->getDataType()->getValue(1);
    this->getOutPort(0)->getDataType()->setValue(0, result);
}
