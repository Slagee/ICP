#include "port.h"

port::port(abstractBlock *parent){
    pressed = false;
    onMouse = false;
    number = 0;
    dragOver = false;
    myParent = parent;
    portWire = nullptr;
    inPort = false;
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setAcceptDrops(true);
}

QRectF port::boundingRect() const { return QRectF(0, 0, 2 * PORT_RADIUS, 2 * PORT_RADIUS); }

void port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF portBox = boundingRect();
    QBrush brush(WIRELESS_UNSET_IN_PORT_COLOR);

    if (inPort) {
        brush.setColor(WIRELESS_UNSET_IN_PORT_COLOR);
    } else {
        brush.setColor(WIRELESS_OUT_PORT_COLOR);
    }

    if (portWire != nullptr) {
        brush.setColor(WIRED_IN_OUT_PORT_COLOR);
    }

    if (onMouse || dragOver) {
        brush.setColor(HOVER_IN_OUT_PORT_COLOR);
    }

    painter->setBrush(brush);
    painter->drawEllipse(portBox);
}

int port::getPortRadius() { return PORT_RADIUS; }

void port::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //qDebug("enter");
    onMouse = true;
    this->update();
    QGraphicsItem::hoverEnterEvent(event);
}

void port::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //qDebug("leave");
    onMouse = false;
    this->update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void port::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug("pressed");
    pressed = true;
    setCursor(Qt::ClosedHandCursor);
    //this->update();
    //QGraphicsItem::mousePressEvent(event);
}

void port::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("realesed");
    pressed = false;
    setCursor(Qt::OpenHandCursor);
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void port::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    portWire = new wire(myParent->startX, myParent->startY, 0, 0, myParent->myParent);

    if (inPort) {
        portWire->setStartPort(this);
    } else {
        portWire->setEndPort(this);
    }

    myParent->myParent->addItem(portWire);

    setCursor(Qt::OpenHandCursor);
    drag->exec();
    if (portWire != nullptr) {
        if (portWire->getStartPort() == nullptr || portWire->getEndPort() == nullptr) {
            qDebug("nicim to tu!");

            if (portWire->getStartPort() != nullptr) {
                portWire->getStartPort()->portWire = nullptr;
            } else if (portWire->getEndPort() != nullptr) {
                portWire->getEndPort()->portWire = nullptr;
            }

            delete myParent->myParent->items().first();
        }
    }
}

void port::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    dragOver = true;
    update();
    Q_UNUSED(event);
}

void port::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    dragOver = false;
    update();
    Q_UNUSED(event);
}

void port::dropEvent(QGraphicsSceneDragDropEvent *event) {
    dragOver = false;

    if (portWire != nullptr) {
        wire *tempWire = qgraphicsitem_cast<wire *>(myParent->myParent->items().first());
        if (tempWire->getEndPort() != nullptr) {
            tempWire->getEndPort()->portWire = nullptr;
        } else if (tempWire->getStartPort() != nullptr) {
            tempWire->getStartPort()->portWire = nullptr;
        }
        delete myParent->myParent->items().first();
    } else {

        portWire = qgraphicsitem_cast<wire *>(myParent->myParent->items().first());

        if (inPort) {
            if (portWire->getStartPort() != nullptr || portWire->getEndPort()->myParent == this->myParent) {
                portWire->getStartPort()->portWire = nullptr;
                delete myParent->myParent->items().first();
                portWire = nullptr;
            } else {
                if (portWire->getEndPort()->myParent == this->myParent) {
                    portWire->getStartPort()->portWire = nullptr;
                    delete myParent->myParent->items().first();
                    portWire = nullptr;
                } else {
                    portWire->setStartPort(this);
                    portWire->dragFinished = true;
                    portWire->update();
                }
            }
        } else {
            if (portWire->getEndPort() != nullptr) {
                portWire->getEndPort()->portWire = nullptr;
                delete myParent->myParent->items().first();
                portWire = nullptr;
            } else {
                if (portWire->getStartPort()->myParent == this->myParent) {
                    portWire->getStartPort()->portWire = nullptr;
                    delete myParent->myParent->items().first();
                    portWire = nullptr;
                } else {
                    portWire->setEndPort(this);
                    portWire->dragFinished = true;
                    portWire->update();
                }
            }
        }
    }
    update();
    Q_UNUSED(event);
}
