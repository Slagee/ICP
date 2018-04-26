#include "port.h"

port::port(){
    pressed = false;
    onMouse = false;
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF port::boundingRect() const { return QRectF(0, 0, 2 * PORT_RADIUS, 2 * PORT_RADIUS); }

void port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qDebug("1 je tu itemu %d", this->childItems().length());
    QRectF portBox = boundingRect();
    QBrush brush(Qt::green);

    if (pressed) {
        brush.setColor(Qt::red);
    } else if (onMouse) {
        brush.setColor(Qt::yellow);
    }

    painter->setBrush(brush);
    painter->drawEllipse(portBox);
    qDebug("2 je tu itemu %d", this->childItems().length());
}

double port::getPortRadius() { return PORT_RADIUS; }

void port::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    qDebug("enter");
    onMouse = true;
    this->update();
    QGraphicsItem::hoverEnterEvent(event);
}

void port::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug("leave");
    onMouse = false;
    this->update();
    QGraphicsItem::hoverLeaveEvent(event);
}
/*
void port::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("pressed");
    pressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void port::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("realesed");
    pressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}
*/
