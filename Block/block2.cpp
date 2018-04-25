#include "block2.h"

Block2::Block2(qreal x, qreal y)
{
    Pressed = false;
    setFlag(ItemIsMovable);
    posX = x;
    posY = y;
}

QRectF Block2::boundingRect() const
{
    return QRectF(posX, posY, 100, 40);
}

void Block2::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (Pressed) {
        brush.setColor(Qt::red);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Block2::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void Block2::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}
