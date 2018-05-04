/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "AbstractType.h"

bool AbstractType::getValuesSet() { return this->valuesSet; }

void AbstractType::setValuesSet(bool value) { this->valuesSet = value; }

void AbstractType::setMyParent(Port *parent) { this->myParent = parent; }
