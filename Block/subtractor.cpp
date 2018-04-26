#include "subtractor.h"

subtractor::subtractor(qreal x, qreal y) {
    Pressed = false;
    setFlag(ItemIsMovable);
    posX = x;
    posY = y;
}

QRectF subtractor::boundingRect() const {
    return QRectF(posX, posY, BLOCK_WIDTH, BLOCK_HEIGHT);
}

void subtractor::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if (Pressed) {
        brush.setColor(Qt::red);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}
