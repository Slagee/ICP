#include "adder.h"

adder::adder(qreal x, qreal y) {
    Pressed = false;
    setFlag(ItemIsMovable);
    posX = x;
    posY = y;
}

void adder::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::green);

    if (Pressed) {
        brush.setColor(Qt::red);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

QRectF adder::boundingRect() const { return QRectF(posX, posY, BLOCK_WIDTH, BLOCK_HEIGHT); }
