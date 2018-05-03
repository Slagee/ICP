#include "Oxid.h"

Oxid::Oxid() {}

double Oxid::getValue(int index) { return this->values[index]; }

void Oxid::setValue(int index, double newValue) { this->values[index] = newValue; }

int Oxid::getValuesLength() { return NUMBER_OF_VALUES; }

QString Oxid::getType() { return  TYPE_NAME; }

QString Oxid::getValueName(int index) { return VALUES_NAMES[index]; }
