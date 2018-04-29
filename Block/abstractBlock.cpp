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
    QFont fontLabels(this->BLOCK_TEXT_FONT, this->BLOCK_LABEL_SIZE);
    QTextOption inPortLabelOptions(Qt::AlignLeft);
    QTextOption outPortLabelOptions(Qt::AlignRight);
    QFontMetrics fontMetrics(fontLabels);

    painter->setFont(fontLabels);

    port *blockPort;

    // cyklus pro nastaveni pripadnych novych zacatku/koncu pripadny dratu na bloku
    for (int i = 0; i < this->childItems().length(); i++) {
        blockPort = qgraphicsitem_cast<port *>(this->childItems()[i]);
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

    QRectF boxForLabel;
    int portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getInPortsCount() + 1);

    for (int i = 1; i <= this->getInPortsCount(); i++) {
        boxForLabel = QRectF(this->startX + this->LABELS_SPACING, this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - fontMetrics.height() / 2, this->getBlockWidth() - this->LABELS_SPACING, fontMetrics.height());
        painter->drawText(boxForLabel, this->getInPortLabel(i - 1), inPortLabelOptions);
    }

    portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getOutPortsCount() + 1);

    for (int i = 1; i <= this->getOutPortsCount(); i++) {
        boxForLabel = QRectF(this->startX, this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - fontMetrics.height() / 2, this->getBlockWidth() - this->LABELS_SPACING, fontMetrics.height());
        painter->drawText(boxForLabel, this->getOutPortLabel(i - 1), outPortLabelOptions);
    }

    // vykresleni tela bloku
    QFont fontName(this->BLOCK_TEXT_FONT, this->BLOCK_NAME_SIZE);
    fontName.setBold(BLOCK_NAME_BOLD);
    QTextOption blockNameOptions(Qt::AlignCenter);
    painter->setFont(fontName);
    painter->drawText(blockBox, this->getBlockName(), blockNameOptions);
    QPen pen;
    pen.setWidth(BLOCK_BORDER_THICKNESS);
    painter->setPen(pen);
    painter->drawRect(this->startX, this->startY, this->getBlockWidth(), this->getBlockHeight());
}

port *abstractBlock::getOutPort(int index) { return qgraphicsitem_cast<port *>(this->childItems()[index + this->getInPortsCount()]); }

port *abstractBlock::getInPort(int index) { return qgraphicsitem_cast<port *>(this->childItems()[index]); }

void abstractBlock::setCalculated(bool value) { this->calculated = value; }

bool abstractBlock::getCalculated() { return this->calculated; }
