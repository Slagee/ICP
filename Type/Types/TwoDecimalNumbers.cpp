#include "TwoDecimalNumbers.h"

TwoDecimalNumbers::TwoDecimalNumbers() {}

double TwoDecimalNumbers::getValue(int index) { return this->values[index]; }

void TwoDecimalNumbers::setValue(int index, double newValue) { this->values[index] = newValue; }

int TwoDecimalNumbers::getValuesLength() { return NUMBER_OF_VALUES; }

QString TwoDecimalNumbers::getType() { return  TYPE_NAME; }

QString TwoDecimalNumbers::getValueName(int index) { return VALUES_NAMES[index]; }
