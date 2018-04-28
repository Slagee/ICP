#include "threedecimalnumbers.h"

threeDecimalNumbers::threeDecimalNumbers(QGraphicsItem *parent) {
    this->myParent = parent;
}

double threeDecimalNumbers::getValue(int index) { return this->values[index]; }

void threeDecimalNumbers::setValue(int index, double newValue) { this->values[index] = newValue; }

int threeDecimalNumbers::getValuesLength() { return NUMBER_OF_VALUES; }

QString threeDecimalNumbers::getType() { return  TYPE_NAME; }

QString threeDecimalNumbers::getValueName(int index) { return VALUES_NAMES[index]; }
