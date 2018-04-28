#include "abstractBlock.h"

QRectF abstractBlock::boundingRect() const { return QRectF(startX, startY, getBlockWidth(), getBlockHeight()); }

void abstractBlock::constructBlock() {
    port *newPort;
    int portsDistance = (getBlockHeight() - 2 * TOP_BOTTOM_SPACING) / (getInPortsCount() + 1);
    for (int i = 1; i <= getInPortsCount(); i++) {
        newPort = new port(this);
        newPort->setX(startX - 2 * newPort->getPortRadius());
        newPort->setY(startY + i * portsDistance + TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->number = i;
        newPort->inPort = true;
        this->addToGroup(newPort);
    }
    portsDistance = (getBlockHeight() - 2 * TOP_BOTTOM_SPACING) / (getOutPortsCount() + 1);
    for (int i = 1; i <= getOutPortsCount(); i++) {
        newPort = new port(this);
        newPort->setX(startX + getBlockWidth());
        newPort->setY(startY + i * portsDistance + TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->number = i;
        addToGroup(newPort);
    }
}

void abstractBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    QRectF blockBox = boundingRect();
    QTextOption blockNameOptions(Qt::AlignCenter);

    for (int i = 0; i < this->childItems().length(); i++) {
        port *blockPort = qgraphicsitem_cast<port *>(this->childItems()[i]);
        if (blockPort->portWire != nullptr) {
            if (blockPort->inPort) {
                blockPort->portWire->shiftStartX = this->x();
                blockPort->portWire->shiftStartY = this->y();
                blockPort->portWire->update();
            } else {
                blockPort->portWire->shiftEndX = this->x();
                blockPort->portWire->shiftEndY = this->y();
                blockPort->portWire->update();
            }
        }
    }

    painter->drawText(blockBox, getBlockName(), blockNameOptions);
    painter->drawRect(startX, startY, getBlockWidth(), getBlockHeight());
}
