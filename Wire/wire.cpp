#include "wire.h"

wire::wire(QGraphicsScene *parent) { this->myParent = parent; }

QRectF wire::boundingRect() const { return QRectF(0, 0, this->myParent->width(), this->myParent->height()); }

void wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    // kdyz je drat z portu do portu
    if (this->startPort != nullptr && this->endPort != nullptr) {
        painter->drawLine(this->startPort->x() + this->shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + this->shiftStartY + this->startPort->getPortRadius(), this->endPort->x() + this->shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + this->shiftEndY + this->endPort->getPortRadius());

    // kdyz je z portu k mysi
    } else if (!this->dragFinished) {
        // ziskani ukazatele na okno
        MainWindow *window = qobject_cast<MainWindow *>(this->myParent->parent());

        //zjisteni polohy mysi v okne
        QPoint mouse = window->mapFromGlobal(QCursor::pos());

        // kdyz se drat tahne z in-portu
        if (this->startPort != nullptr) {
            painter->drawLine(this->startPort->x() + this->shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + this->shiftStartY + this->startPort->getPortRadius(), mouse.x() - window->toolBarWidth, mouse.y() - window->menuHeight);

        // kdyz se drat tahne z out-portu
        } else if (this->endPort != nullptr) {
            painter->drawLine(mouse.x() - window->toolBarWidth, mouse.y() - window->menuHeight, this->endPort->x() + this->shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + this->shiftEndY + this->endPort->getPortRadius());
        }
    }
}

void wire::setStartPort(port *port) { this->startPort = port; }

void wire::setEndPort(port *port) { this->endPort = port; }

port *wire::getStartPort() { return this->startPort; }

port *wire::getEndPort() { return this->endPort; }

void wire::setDragFinished(bool value) { this->dragFinished = value; }

void wire::setShiftStartX(int value) { this->shiftStartX = value; }

void wire::setShiftStartY(int value) { this->shiftStartY = value; }

void wire::setShiftEndX(int value) { this->shiftEndX = value; }

void wire::setShiftEndY(int value) { this->shiftEndY = value; }