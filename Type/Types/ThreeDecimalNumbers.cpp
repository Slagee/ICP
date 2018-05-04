/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "ThreeDecimalNumbers.h"

ThreeDecimalNumbers::ThreeDecimalNumbers() {}

double ThreeDecimalNumbers::getValue(int index) { return this->values[index]; }

void ThreeDecimalNumbers::setValue(int index, double newValue) { this->values[index] = newValue; }

int ThreeDecimalNumbers::getValuesLength() { return NUMBER_OF_VALUES; }

QString ThreeDecimalNumbers::getType() { return  TYPE_NAME; }

QString ThreeDecimalNumbers::getValueName(int index) { return VALUES_NAMES[index]; }
