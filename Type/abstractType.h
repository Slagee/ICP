#ifndef ABSTRACTTYPE_H
#define ABSTRACTTYPE_H

#include <QString>
#include <QGraphicsItem>

// abstraktni trida pro typy
class abstractType {
private:
    bool valuesSet = false;

public:
    bool getValuesSet();
    void setValuesSet(bool value);

    virtual double getValue(int index) = 0;
    virtual void setValue(int index, double newValue) = 0;
    virtual int getValuesLength() = 0;
    virtual QString getType() = 0;
    virtual QString getValueName(int index) = 0;
};

#endif // ABSTRACTTYPE_H