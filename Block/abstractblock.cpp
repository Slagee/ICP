#include "abstractblock.h"

QRectF abstractblock::boundingRect() const { return QRectF(startX, startY, getBlockWidth(), getBlockHeight()); }

void abstractblock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::green);


    if (Pressed) { brush.setColor(Qt::red); }

    for (int i = 0; i < getInPortsCount(); i++) {

    }

    for (int i = 0; i < getOutPortsCount(); i++) {

    }

    painter->drawEllipse(startX, startY, PORT_RADIUS * 2, PORT_RADIUS * 2);
    painter->drawEllipse(startX + getBlockWidth() - PORT_RADIUS * 2, startY, PORT_RADIUS * 2, PORT_RADIUS * 2);
    painter->drawEllipse(startX + getBlockWidth() - PORT_RADIUS * 2, startY + getBlockHeight() - PORT_RADIUS * 2, PORT_RADIUS * 2, PORT_RADIUS * 2);
    painter->drawEllipse(startX, startY + getBlockHeight() - PORT_RADIUS * 2, PORT_RADIUS * 2, PORT_RADIUS * 2);
    painter->drawRect(startX + PORT_RADIUS * 2, startY, getBlockWidth() - 4 * PORT_RADIUS, getBlockHeight());
    painter->fillRect(startX + PORT_RADIUS * 2 + 1, startY + 1, getBlockWidth() - 4 * PORT_RADIUS - 1, getBlockHeight() - 1, brush);
}

void abstractblock::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Pressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void abstractblock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Pressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}
