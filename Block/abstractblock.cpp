#include "abstractblock.h"

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
