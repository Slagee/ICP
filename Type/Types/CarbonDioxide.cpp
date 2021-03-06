/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "CarbonDioxide.h"

CarbonDioxide::CarbonDioxide() {}

double CarbonDioxide::getValue(int index) { return this->values[index]; }

void CarbonDioxide::setValue(int index, double newValue) { this->values[index] = newValue; }

int CarbonDioxide::getValuesLength() { return NUMBER_OF_VALUES; }

QString CarbonDioxide::getType() { return  TYPE_NAME; }

QString CarbonDioxide::getValueName(int index) { return VALUES_NAMES[index]; }
