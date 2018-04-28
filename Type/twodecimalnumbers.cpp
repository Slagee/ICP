#include "twodecimalnumbers.h"

twoDecimalNumbers::twoDecimalNumbers(QGraphicsItem *parent) {
    this->myParent = parent;
}

double twoDecimalNumbers::getValue(int index) { return this->values[index]; }

void twoDecimalNumbers::setValue(int index, double newValue) { this->values[index] = newValue; }

int twoDecimalNumbers::getValuesLength() { return NUMBER_OF_VALUES; }

QString twoDecimalNumbers::getType() { return  TYPE_NAME; }

QString twoDecimalNumbers::getValueName(int index) { return VALUES_NAMES[index]; }
