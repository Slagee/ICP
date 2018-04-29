#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QPainter>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>
#include <QFontMetrics>
#include <QTextOption>

#include "../Port/port.h"

class abstractblock : public QGraphicsItemGroup {
public:
    const int TOP_BOTTOM_SPACING = -5;
    bool pressed;
    qreal startX;
    qreal startY;

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
};

#endif // ABSTRACTBLOCK_H
