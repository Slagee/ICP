#ifndef ONEDECIMALNUMBER_H
#define ONEDECIMALNUMBER_H

#include "abstractType.h"

class oneDecimalNumber : public abstractType {

private:
    const QString TYPE_NAME = "One Decimal Number";
    const static int NUMBER_OF_VALUES = 1;
    const QString VALUES_NAMES[NUMBER_OF_VALUES] = {"Decimal number"};

    double values[NUMBER_OF_VALUES] = {0};

public:
    oneDecimalNumber();

    double getValue(int index);
    void setValue(int index, double newValue);
    int getValuesLength();
    QString getType();
    QString getValueName(int index);
};

#endif // ONEDECIMALNUMBER_H
