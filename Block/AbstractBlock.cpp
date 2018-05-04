/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "AbstractBlock.h"

QRectF AbstractBlock::boundingRect() const { return QRectF(this->startX, this->startY, this->getBlockWidth(), this->getBlockHeight()); }

void AbstractBlock::constructBlock() {
    Port *newPort;

    // vzdalenost mezi stredy portu
    int portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getInPortsCount() + 1);

    // cyklus pro vytvoreni in-portu
    for (int i = 1; i <= this->getInPortsCount(); i++) {
        newPort = new Port(this->getInPortDataType(i - 1), this);
        newPort->setX(this->startX - 2 * newPort->getPortRadius());
        newPort->setY(this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->setInPort(true);
        this->addToGroup(newPort);
    }

    portsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getOutPortsCount() + 1);

    // cyklus pro vytvoreni out-portu
    for (int i = 1; i <= this->getOutPortsCount(); i++) {
        newPort = new Port(this->getOutPortDataType(i - 1), this);
        newPort->setX(this->startX + this->getBlockWidth());
        newPort->setY(this->startY + i * portsDistance + this->TOP_BOTTOM_SPACING - newPort->getPortRadius());
        newPort->setInPort(false);
        this->addToGroup(newPort);
    }
}

void AbstractBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {

    // telo bloku
    QRectF blockBox = boundingRect();

    // nastaveni fontu pro texty na bloku
    QFont fontLabels(this->BLOCK_TEXT_FONT, this->BLOCK_LABEL_SIZE);
    QTextOption inPortLabelOptions(Qt::AlignLeft);
    QTextOption outPortLabelOptions(Qt::AlignRight);
    QFontMetrics fontMetrics(fontLabels);
    painter->setFont(fontLabels);

    Port *blockPort;

    // cyklus pro nastaveni pripadnych novych zacatku/koncu dratu na bloku
    for (int i = 0; i < this->childItems().length(); i++) {
        blockPort = qgraphicsitem_cast<Port *>(this->childItems()[i]);
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

    // oblast pro popisky
    QRectF boxForLabel;

    // vzdalenost mezi
    int portsLabelsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getInPortsCount() + 1);

    // vykresleni popisku in-portu
    for (int i = 1; i <= this->getInPortsCount(); i++) {
        boxForLabel = QRectF(this->startX + this->LABELS_SPACING, this->startY + i * portsLabelsDistance + this->TOP_BOTTOM_SPACING - fontMetrics.height() / 2, this->getBlockWidth() - this->LABELS_SPACING, fontMetrics.height());
        painter->drawText(boxForLabel, this->getInPortLabel(i - 1), inPortLabelOptions);
    }

    portsLabelsDistance = (this->getBlockHeight() - 2 * this->TOP_BOTTOM_SPACING) / (this->getOutPortsCount() + 1);

    // vykresleni popisku out-portu
    for (int i = 1; i <= this->getOutPortsCount(); i++) {
        boxForLabel = QRectF(this->startX, this->startY + i * portsLabelsDistance + this->TOP_BOTTOM_SPACING - fontMetrics.height() / 2, this->getBlockWidth() - this->LABELS_SPACING, fontMetrics.height());
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

    Q_UNUSED(options);
    Q_UNUSED(widget);
}

Port *AbstractBlock::getOutPort(int index) { return qgraphicsitem_cast<Port *>(this->childItems()[index + this->getInPortsCount()]); }

Port *AbstractBlock::getInPort(int index) { return qgraphicsitem_cast<Port *>(this->childItems()[index]); }

void AbstractBlock::setCalculated(bool value) { this->calculated = value; }

bool AbstractBlock::getCalculated() { return this->calculated; }

void AbstractBlock::setBlockBorderColor(QColor color) { this->blockBorderColor = color; }

QColor AbstractBlock::getBlockBorderColor() { return this->blockBorderColor; }

QColor AbstractBlock::getDefaultBorderColor() { return this->DEFAULT_BLOCK_COLOR; }

QColor AbstractBlock::getActualBorderColor() { return this->ACTUAL_BLOCK_COLOR; }

QColor AbstractBlock::getNotCalculatedBorderColor() { return this->NOT_CALCULATED_BLOCK_COLOR; }

QColor AbstractBlock::getCalculatedBorderColor() { return this->CALCULATED_BLOCK_COLOR; }

QColor AbstractBlock::getLastCalculatedBorderColor() { return this->LAST_CALCULATED_BLOCK_COLOR; }

void AbstractBlock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    // doraz na smazani bloku + pripadne smazani bloku
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

    Q_UNUSED(event);
}

void AbstractBlock::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    // formular pro vyplneni vstupnich portu bloku
    if(event->button()==Qt::RightButton){
        FillValuesBlock fillValuesBlock(this);
        fillValuesBlock.setModal(true);
        fillValuesBlock.exec();
    }
}
