#ifndef THREEDECIMALNUMBERS_H
#define THREEDECIMALNUMBERS_H

#include "abstractType.h"

class threeDecimalNumbers : public abstractType {
private:
    const QString TYPE_NAME = "Three Decimal Number";
    const static int NUMBER_OF_VALUES = 3;
    const QString VALUES_NAMES[NUMBER_OF_VALUES] = {"Decimal number", "Decimal number", "Decimal number"};

    double values[NUMBER_OF_VALUES] = {0, 0, 0};

public:
    threeDecimalNumbers();

    double getValue(int index);
    void setValue(int index, double newValue);
    int getValuesLength();
    QString getType();
    QString getValueName(int index);
};

#endif // THREEDECIMALNUMBERS_H
