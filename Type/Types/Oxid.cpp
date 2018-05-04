/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Oxid.h"

Oxid::Oxid() {}

double Oxid::getValue(int index) { return this->values[index]; }

void Oxid::setValue(int index, double newValue) { this->values[index] = newValue; }

int Oxid::getValuesLength() { return NUMBER_OF_VALUES; }

QString Oxid::getType() { return  TYPE_NAME; }

QString Oxid::getValueName(int index) { return VALUES_NAMES[index]; }
