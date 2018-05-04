/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "WaterLaboratory.h"

WaterLaboratory::WaterLaboratory(int x, int y, QGraphicsScene *parent) {
    this->startX = x - this->BLOCK_WIDTH / 2;
    this->startY = y - this->BLOCK_HEIGHT / 2;
    this->myParent = parent;

    this->setFlag(ItemIsMovable);
    this->setHandlesChildEvents(false);
    this->constructBlock();
}

int WaterLaboratory::getBlockWidth() const { return BLOCK_WIDTH; }

int WaterLaboratory::getBlockHeight() const { return BLOCK_HEIGHT; }

int WaterLaboratory::getInPortsCount() const { return IN_PORTS_COUNT; }

int WaterLaboratory::getOutPortsCount() const { return OUT_PORTS_COUNT; }

QString WaterLaboratory::getBlockClassName() const { return BLOCK_CLASS_NAME; }

QString WaterLaboratory::getBlockName() const { return BLOCK_NAME; }

QString WaterLaboratory::getInPortLabel(int index) const { return IN_PORTS_LABELS[index]; }

QString WaterLaboratory::getOutPortLabel(int index) const { return OUT_PORTS_LABELS[index]; }

QString WaterLaboratory::getInPortDataType(int index) const { return IN_PORTS_DATA_TYPES[index]; }

QString WaterLaboratory::getOutPortDataType(int index) const { return OUT_PORTS_DATA_TYPES[index]; }

void WaterLaboratory::doCalculation() {
    double relativeWeightH = 1.00784;
    double relativeWeightO = 15.9994;
    double relativeWeightC = 12.0107;
    double hydrogenium = this->getInPort(0)->getDataType()->getValue(0);
    double oxid = this->getInPort(1)->getDataType()->getValue(0);
    double methan = this->getInPort(2)->getDataType()->getValue(0);
    double water = 0;
    double carbonDioxide = 0;

    if (hydrogenium / (4 * relativeWeightH) < oxid / (2 * relativeWeightO)) {
        water = hydrogenium;
        oxid = oxid - hydrogenium * ((2 * relativeWeightO) / (4 * relativeWeightH));
        hydrogenium = 0;
    } else {
        water = oxid;
        hydrogenium = hydrogenium - oxid * ((4 * relativeWeightH) / (2 * relativeWeightO));
    }

    if (methan / (4 * relativeWeightH + relativeWeightC) < oxid / (2 * relativeWeightO)) {
        water += methan * ((4 * relativeWeightH) / relativeWeightC);
        carbonDioxide = ((methan - methan * ((4 * relativeWeightH) / relativeWeightC)) / relativeWeightC) * (relativeWeightC + 2 * relativeWeightO);
        oxid = oxid - ((methan - methan * ((4 * relativeWeightH) / relativeWeightC)) / relativeWeightC) * (4 * relativeWeightO);
        methan = 0;
    } else {
        water += oxid / 2;
        carbonDioxide = ((oxid / 2) / (2 * relativeWeightO)) * (2 * relativeWeightO + relativeWeightC);
        methan = methan - ((oxid / 2) / (2 * relativeWeightO)) * (4 * relativeWeightH + relativeWeightC);
        oxid = 0;
    }

    this->getOutPort(0)->getDataType()->setValue(0, water);
    this->getOutPort(1)->getDataType()->setValue(0, carbonDioxide);
    this->getOutPort(2)->getDataType()->setValue(0, hydrogenium);
    this->getOutPort(3)->getDataType()->setValue(0, oxid);
    this->getOutPort(4)->getDataType()->setValue(0, methan);
}
