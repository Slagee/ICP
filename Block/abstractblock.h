#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>

class abstractblock : public QGraphicsItem {
public:
    const int PORT_RADIUS = 7;

    bool Pressed;
    qreal startX;
    qreal startY;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    QRectF boundingRect() const;

    virtual int getBlockWidth() const = 0;
    virtual int getBlockHeight() const = 0;
    virtual int getInPortsCount() const = 0;
    virtual int getOutPortsCount() const = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ABSTRACTBLOCK_H
