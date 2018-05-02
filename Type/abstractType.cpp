#include "abstractType.h"

bool abstractType::getValuesSet() { return this->valuesSet; }

void abstractType::setValuesSet(bool value) { this->valuesSet = value; }

void abstractType::setMyParent(port *parent) { this->myParent = parent; }
