#include "abstractBlock.h"

QRectF abstractBlock::boundingRect() const { return QRectF(this->startX, this->startY, this->getBlockWidth(), this->getBlockHeight()); }

void abstractBlock::constructBlock() {
    // ukazatel na port, pro vytvoreni vsech portu
    port *newPort;

    // pro vzdalenost mezi porty
    int portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getInPortsCount() + 1);

    // cyklus pro vytvoreni in-portu
    for (int i = 1; i <= this->getInPortsCount(); i++) {
        newPort = new port(this);
        newPort->setX(this->startX - 2 * newPort->getPortRadius());
        newPort->setY(this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->setInPort(true);
        this->addToGroup(newPort);
    }

    portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getOutPortsCount() + 1);

    // cyklus pro vytvoreni out-portu
    for (int i = 1; i <= this->getOutPortsCount(); i++) {
        newPort = new port(this);
        newPort->setX(this->startX + this->getBlockWidth());
        newPort->setY(this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->setInPort(false);
        this->addToGroup(newPort);
    }
}

void abstractBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    // pro telo bloku
    QRectF blockBox = boundingRect();

    // pro umisteni textu v bloku
    QTextOption blockNameOptions(Qt::AlignCenter);

    // cyklus pro nastaveni pripadnych novych zacatku/koncu pripadny dratu na bloku
    for (int i = 0; i < this->childItems().length(); i++) {
        port *blockPort = qgraphicsitem_cast<port *>(this->childItems()[i]);
        if (blockPort->portWire != nullptr) {
            if (blockPort->getInPort()) {
                blockPort->portWire->setShiftStartX(this->x());
                blockPort->portWire->setShiftStartY(this->y());
                blockPort->portWire->update();
            } else {
                blockPort->portWire->setShiftEndX(this->x());
                blockPort->portWire->setShiftEndY(this->y());
                blockPort->portWire->update();
            }
        }
    }

    // vykresleni tela bloku
    painter->drawText(blockBox, this->getBlockName(), blockNameOptions);
    painter->drawRect(this->startX, this->startY, this->getBlockWidth(), this->getBlockHeight());
}
