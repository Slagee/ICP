#include "abstractblock.h"

QRectF abstractblock::boundingRect() const { return QRectF(startX, startY, getBlockWidth(), getBlockHeight()); }

void abstractblock::constructBlock() {
    port *newPort;
    int portsDistance = (getBlockHeight() - 2 * TOP_BOTTOM_SPACING) / (getInPortsCount() + 1);
    for (int i = 1; i <= getInPortsCount(); i++) {
        newPort = new port();
        newPort->setX(startX - 2 * newPort->getPortRadius());
        newPort->setY(startY + i * portsDistance + TOP_BOTTOM_SPACING - newPort->getPortRadius());
        this->addToGroup(newPort);
    }
    portsDistance = (getBlockHeight() - 2 * TOP_BOTTOM_SPACING) / (getOutPortsCount() + 1);
    for (int i = 1; i <= getOutPortsCount(); i++) {
        newPort = new port();
        newPort->setX(startX + getBlockWidth());
        newPort->setY(startY + i * portsDistance + TOP_BOTTOM_SPACING - newPort->getPortRadius());
        this->addToGroup(newPort);
    }
    QGraphicsItemGroup::setHandlesChildEvents(false);
}

void abstractblock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF blockBox = boundingRect();
    QBrush brush(Qt::green);
    QTextOption blockNameOptions(Qt::AlignCenter);

    if (pressed) { brush.setColor(Qt::red); }

    painter->fillRect(blockBox, brush);
    painter->drawRect(blockBox);
    painter->drawText(blockBox, getBlockName(), blockNameOptions);
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

