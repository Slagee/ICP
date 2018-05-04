/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Water.h"

Water::Water() {}

double Water::getValue(int index) { return this->values[index]; }

void Water::setValue(int index, double newValue) { this->values[index] = newValue; }

int Water::getValuesLength() { return NUMBER_OF_VALUES; }

QString Water::getType() { return  TYPE_NAME; }

QString Water::getValueName(int index) { return VALUES_NAMES[index]; }
