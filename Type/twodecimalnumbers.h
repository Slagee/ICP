#ifndef TWODECIMALNUMBERS_H
#define TWODECIMALNUMBERS_H

#include "abstractType.h"

class twoDecimalNumbers : public abstractType {
private:
    const QString TYPE_NAME = "Two Decimal Number";
    const static int NUMBER_OF_VALUES = 3;
    const QString VALUES_NAMES[NUMBER_OF_VALUES] = {"Decimal number", "Decimal number"};

    double values[NUMBER_OF_VALUES] = {0, 0};
    QGraphicsItem *myParent;

public:
    twoDecimalNumbers(QGraphicsItem *parent);

    double getValue(int index);
    void setValue(int index, double newValue);
    int getValuesLength();
    QString getType();
    QString getValueName(int index);
};

#endif // TWODECIMALNUMBERS_H
