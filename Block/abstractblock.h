#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>

class abstractblock : public QGraphicsItem {
public:
    bool Pressed;
    qreal posX;
    qreal posY;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) = 0;
    QRectF boundingRect() const = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ABSTRACTBLOCK_H
