#include "Methan.h"

Methan::Methan() {}

double Methan::getValue(int index) { return this->values[index]; }

void Methan::setValue(int index, double newValue) { this->values[index] = newValue; }

int Methan::getValuesLength() { return NUMBER_OF_VALUES; }

QString Methan::getType() { return  TYPE_NAME; }

QString Methan::getValueName(int index) { return VALUES_NAMES[index]; }
