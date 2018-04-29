#include "onedecimalnumber.h"

oneDecimalNumber::oneDecimalNumber(QGraphicsItem *parent) {
    this->myParent = parent;
}

double oneDecimalNumber::getValue(int index) { return this->values[index]; }

void oneDecimalNumber::setValue(int index, double newValue) { this->values[index] = newValue; }

int oneDecimalNumber::getValuesLength() { return NUMBER_OF_VALUES; }

QString oneDecimalNumber::getType() { return  TYPE_NAME; }

QString oneDecimalNumber::getValueName(int index) { return VALUES_NAMES[index]; }
