#include "AbstractType.h"

bool AbstractType::getValuesSet() { return this->valuesSet; }

void AbstractType::setValuesSet(bool value) { this->valuesSet = value; }

void AbstractType::setMyParent(Port *parent) { this->myParent = parent; }
