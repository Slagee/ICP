#ifndef BLOCK2_H
#define BLOCK2_H
#include <QPainter>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QString>

class Block2 : public QGraphicsItem
{
public:
    Block2(qreal x, qreal y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
    bool Pressed;
    qreal posX;
    qreal posY;

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BLOCK2_H
