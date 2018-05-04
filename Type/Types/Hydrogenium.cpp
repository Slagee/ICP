/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Hydrogenium.h"

Hydrogenium::Hydrogenium() {}

double Hydrogenium::getValue(int index) { return this->values[index]; }

void Hydrogenium::setValue(int index, double newValue) { this->values[index] = newValue; }

int Hydrogenium::getValuesLength() { return NUMBER_OF_VALUES; }

QString Hydrogenium::getType() { return  TYPE_NAME; }

QString Hydrogenium::getValueName(int index) { return VALUES_NAMES[index]; }
