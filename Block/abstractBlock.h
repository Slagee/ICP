#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QPainter>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>
#include <QTextOption>

#include "../Port/port.h"

class adder;
class substractor;

class abstractBlock : public QGraphicsItemGroup {
public:
    const int TOP_BOTTOM_SPACING = -5;

    bool pressed;
    int startX;
    int startY;
    QGraphicsScene *myParent;

    void constructBlock();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    QRectF boundingRect() const;

    virtual int getBlockWidth() const = 0;
    virtual int getBlockHeight() const = 0;
    virtual int getInPortsCount() const = 0;
    virtual int getOutPortsCount() const = 0;
    virtual QString getBlockName() const = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // QGraphicsItem interface
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // ABSTRACTBLOCK_H
