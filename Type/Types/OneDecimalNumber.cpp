/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "OneDecimalNumber.h"

OneDecimalNumber::OneDecimalNumber() {}

double OneDecimalNumber::getValue(int index) { return this->values[index]; }

void OneDecimalNumber::setValue(int index, double newValue) { this->values[index] = newValue; }

int OneDecimalNumber::getValuesLength() { return NUMBER_OF_VALUES; }

QString OneDecimalNumber::getType() { return  TYPE_NAME; }

QString OneDecimalNumber::getValueName(int index) { return VALUES_NAMES[index]; }
