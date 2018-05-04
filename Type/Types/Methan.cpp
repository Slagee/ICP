/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Methan.h"

Methan::Methan() {}

double Methan::getValue(int index) { return this->values[index]; }

void Methan::setValue(int index, double newValue) { this->values[index] = newValue; }

int Methan::getValuesLength() { return NUMBER_OF_VALUES; }

QString Methan::getType() { return  TYPE_NAME; }

QString Methan::getValueName(int index) { return VALUES_NAMES[index]; }
