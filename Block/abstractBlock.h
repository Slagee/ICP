#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QPainter>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>
#include <QTextOption>

#include "../Port/port.h"

class wire;
class port;
class abstractBlock;

// abstraktni trida pro bloky
class abstractBlock : public QGraphicsItemGroup {
private:
    // konstanta pro upravu pozice portu na bloku
    const int TOP_BOTTOM_SPACING = -5;

    // je blok propocitany...
    bool calculated = false;

public:
    // prvotni pozice bloku po natazeni na canvas
    int startX = 0;
    int startY = 0;

    // ukazatel na otce
    QGraphicsScene *myParent = nullptr;

    // pro sestaveni bloku
    void constructBlock();

    // pro malovani bloku
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    // pro oblast bloku
    QRectF boundingRect() const;

    // metody implementovane jednotlivymi bloky, pro ziskani informaci o nich
    virtual int getBlockWidth() const = 0;
    virtual int getBlockHeight() const = 0;
    virtual int getInPortsCount() const = 0;
    virtual int getOutPortsCount() const = 0;
    virtual QString getBlockName() const = 0;
    virtual QString getInPortLabel(int index) const = 0;
    virtual QString getOutPortLabel(int index) const = 0;
    virtual void doCalculation() = 0;

    port *getOutPort(int index);
    port *getInPort(int index);
    void setCalculated(bool value);
    bool getCalculated();
};

#endif // ABSTRACTBLOCK_H
