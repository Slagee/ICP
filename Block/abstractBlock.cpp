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
        if (blockPort->getWire() != nullptr) {
            if (blockPort->getInPort()) {
                blockPort->getWire()->setShiftStartX(this->x());
                blockPort->getWire()->setShiftStartY(this->y());
                blockPort->getWire()->update();
            } else {
                blockPort->getWire()->setShiftEndX(this->x());
                blockPort->getWire()->setShiftEndY(this->y());
                blockPort->getWire()->update();
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
    pen.setColor(blockBorderColor);
    painter->setPen(pen);
    painter->drawRect(this->startX, this->startY, this->getBlockWidth(), this->getBlockHeight());
}

port *abstractBlock::getOutPort(int index) { return qgraphicsitem_cast<port *>(this->childItems()[index + this->getInPortsCount()]); }

port *abstractBlock::getInPort(int index) { return qgraphicsitem_cast<port *>(this->childItems()[index]); }

void abstractBlock::setCalculated(bool value) { this->calculated = value; }

bool abstractBlock::getCalculated() { return this->calculated; }

void abstractBlock::setBlockBorderColor(QColor color) { this->blockBorderColor = color; }

QColor abstractBlock::getBlockBorderColor() { return this->blockBorderColor; }

QColor abstractBlock::getDefaultBorderColor() { return this->DEFAULT_BLOCK_COLOR; }

QColor abstractBlock::getActualBorderColor() { return this->ACTUAL_BLOCK_COLOR; }

QColor abstractBlock::getNotCalculatedBorderColor() { return this->NOT_CALCULATED_BLOCK_COLOR; }

QColor abstractBlock::getCalculatedBorderColor() { return this->CALCULATED_BLOCK_COLOR; }

QColor abstractBlock::getLastCalculatedBorderColor() { return this->LAST_CALCULATED_BLOCK_COLOR; }

void abstractBlock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QMessageBox::StandardButton deleteBlock;
    deleteBlock = QMessageBox::question(nullptr, "Delete", "Do you really want to delete this block?", QMessageBox::Yes|QMessageBox::No);
    if (deleteBlock == QMessageBox::Yes) {
        for (int i = 0; i < this->getInPortsCount(); i++) {
            if (this->getInPort(i)->getWire() != nullptr) {
                this->getInPort(i)->getWire()->getOtherPort(this->getInPort(i))->setWire(nullptr);
                delete this->getInPort(i)->getWire();
                this->getInPort(i)->setWire(nullptr);
            }
        }
        for (int i = 0; i < this->getOutPortsCount(); i++) {
            if (this->getOutPort(i)->getWire() != nullptr) {
                this->getOutPort(i)->getWire()->getOtherPort(this->getOutPort(i))->setWire(nullptr);
                delete this->getOutPort(i)->getWire();
                this->getOutPort(i)->setWire(nullptr);
            }
        }
        delete this;
    }
}
