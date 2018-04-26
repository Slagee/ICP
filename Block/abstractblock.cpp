#include "abstractblock.h"

QRectF abstractblock::boundingRect() const { return QRectF(startX, startY, getBlockWidth(), getBlockHeight()); }

void abstractblock::constructBlock() {
    port *newport = new port(startX - 2 * PORT_RADIUS, startY);
    this->addToGroup(newport);
}

void abstractblock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF blockBox = boundingRect();
    QBrush brush(Qt::green);


    if (pressed) { brush.setColor(Qt::red); }

    for (int i = 0; i < getInPortsCount(); i++) {

    }

    for (int i = 0; i < getOutPortsCount(); i++) {

    }

    //painter->drawEllipse((QGraphicsItem) this->childItems().last()->);
    //painter->drawEllipse(startX, startY, PORT_RADIUS * 2, PORT_RADIUS * 2);
    //painter->drawEllipse(startX + getBlockWidth() - PORT_RADIUS * 2, startY, PORT_RADIUS * 2, PORT_RADIUS * 2);
    //painter->drawEllipse(startX + getBlockWidth() - PORT_RADIUS * 2, startY + getBlockHeight() - PORT_RADIUS * 2, PORT_RADIUS * 2, PORT_RADIUS * 2);
    //painter->drawEllipse(startX, startY + getBlockHeight() - PORT_RADIUS * 2, PORT_RADIUS * 2, PORT_RADIUS * 2);
    //painter->fillRect(startX + PORT_RADIUS * 2 + 1, startY + 1, getBlockWidth() - 4 * PORT_RADIUS - 1, getBlockHeight() - 1, brush);
    painter->drawRect(startX, startY, getBlockWidth(), getBlockHeight());
}

void abstractblock::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    pressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void abstractblock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    pressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}
