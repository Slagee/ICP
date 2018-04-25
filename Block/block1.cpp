#include "block1.h"

Block1::Block1()
{
    Pressed = false;
    setFlag(ItemIsMovable);
}

QRectF Block1::boundingRect() const
{
    return QRectF(0,0,100,40);
}

void Block1::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (Pressed) {
        brush.setColor(Qt::red);
    } else {
        brush.setColor(Qt::green);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Block1::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void Block1::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}
