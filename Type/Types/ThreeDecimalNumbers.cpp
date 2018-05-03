#include "ThreeDecimalNumbers.h"

ThreeDecimalNumbers::ThreeDecimalNumbers() {}

double ThreeDecimalNumbers::getValue(int index) { return this->values[index]; }

void ThreeDecimalNumbers::setValue(int index, double newValue) { this->values[index] = newValue; }

int ThreeDecimalNumbers::getValuesLength() { return NUMBER_OF_VALUES; }

QString ThreeDecimalNumbers::getType() { return  TYPE_NAME; }

QString ThreeDecimalNumbers::getValueName(int index) { return VALUES_NAMES[index]; }
