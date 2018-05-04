/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Wire.h"

Wire::Wire(QGraphicsScene *parent) {
    this->myParent = parent;
    this->setAcceptHoverEvents(true);
}

QRectF Wire::boundingRect() const { return QRectF(0, 0, this->myParent->width(), this->myParent->height()); }

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen pen;
    pen.setWidth(WIRE_THICKNESS);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);

    // kdyz je drat z portu do portu
    if (this->startPort != nullptr && this->endPort != nullptr) {
        this->setLine(this->startPort->x() + this->shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + this->shiftStartY + this->startPort->getPortRadius(), this->endPort->x() + this->shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + this->shiftEndY + this->endPort->getPortRadius());
        painter->drawLine(this->line());

    // kdyz je z portu k mysi
    } else if (!this->dragFinished) {
        // ziskani ukazatele na okno
        MainWindow *window = qobject_cast<MainWindow *>(this->myParent->parent());

        //zjisteni polohy mysi v okne
        QPoint mouse = window->mapFromGlobal(QCursor::pos());

        // kdyz se drat tahne z in-portu
        if (this->startPort != nullptr) {
            this->setLine(this->startPort->x() + this->shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + this->shiftStartY + this->startPort->getPortRadius(), mouse.x() - window->getToolbarWidth() - 2 * window->getToolbarMargin(), mouse.y() - window->getMenuHeight());
            painter->drawLine(this->line());

        // kdyz se drat tahne z out-portu
        } else if (this->endPort != nullptr) {
            this->setLine(mouse.x() - window->getToolbarWidth() - 2 * window->getToolbarMargin(), mouse.y() - window->getMenuHeight(), this->endPort->x() + this->shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + this->shiftEndY + this->endPort->getPortRadius());
            painter->drawLine(this->line());
        }
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Wire::setStartPort(Port *port) { this->startPort = port; }

void Wire::setEndPort(Port *port) { this->endPort = port; }

Port *Wire::getStartPort() { return this->startPort; }

Port *Wire::getEndPort() { return this->endPort; }

Port *Wire::getOtherPort(Port *somePort) {
    if (somePort == this->startPort) { return this->endPort; }
    if (somePort == this->endPort) { return this->startPort; }
    return nullptr;
}

void Wire::setDragFinished(bool value) { this->dragFinished = value; }

void Wire::setShiftStartX(int value) { this->shiftStartX = value; }

void Wire::setShiftStartY(int value) { this->shiftStartY = value; }

void Wire::setShiftEndX(int value) { this->shiftEndX = value; }

void Wire::setShiftEndY(int value) { this->shiftEndY = value; }

void Wire::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    this->setToolTip(this->getStartPort()->createToolTip());
    this->update();
    QGraphicsLineItem::hoverEnterEvent(event);
}
