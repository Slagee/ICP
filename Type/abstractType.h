#ifndef ABSTRACTTYPE_H
#define ABSTRACTTYPE_H

#include <QString>
#include <QGraphicsItem>
#include <QMetaType>
#include <QDebug>

class oneDecimalNumber;
class twoDecimalNumbers;
class threeDecimalNumbers;
class port;

// abstraktni trida pro typy
class abstractType {
private:
    bool valuesSet = false;

public:
    port *myParent = nullptr;

    bool getValuesSet();
    void setValuesSet(bool value);
    void setMyParent(port *parent);

    virtual double getValue(int index) = 0;
    virtual void setValue(int index, double newValue) = 0;
    virtual int getValuesLength() = 0;
    virtual QString getType() = 0;
    virtual QString getValueName(int index) = 0;
};

void registrTypes();

#endif // ABSTRACTTYPE_H
