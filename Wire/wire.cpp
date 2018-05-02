#include "wire.h"
#include <QToolTip>

wire::wire(QGraphicsScene *parent) {
    this->myParent = parent;
    this->setAcceptHoverEvents(true);


    //this->setAcceptDrops(true);
    //this->setAcceptTouchEvents(this);
    //this->setActive(true);

    //this->setFlags(ItemIsMovable);
    //this->setHandlesChildEvents(false);
}

QRectF wire::boundingRect() const { return QRectF(0, 0, this->myParent->width(), this->myParent->height()); }
//QRectF wire::boundingRect() const { return QRectF(this->startPort->x() + this->shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + this->shiftStartY + this->startPort->getPortRadius(),100, 100); }

void wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    //painter->setClipRect( option->exposedRect );

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
}

void wire::setStartPort(port *port) { this->startPort = port; }

void wire::setEndPort(port *port) { this->endPort = port; }

port *wire::getStartPort() { return this->startPort; }

port *wire::getEndPort() { return this->endPort; }

port *wire::getOtherPort(port *somePort) {
    if (somePort == this->startPort) { return this->endPort; }
    if (somePort == this->endPort) { return this->startPort; }
    return nullptr;
}

void wire::setDragFinished(bool value) { this->dragFinished = value; }

void wire::setShiftStartX(int value) { this->shiftStartX = value; }

void wire::setShiftStartY(int value) { this->shiftStartY = value; }

void wire::setShiftEndX(int value) { this->shiftEndX = value; }

void wire::setShiftEndY(int value) { this->shiftEndY = value; }

void wire::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    qDebug("hover...");
    this->setToolTip(this->getStartPort()->createToolTip());
    this->update();
    QGraphicsLineItem::hoverEnterEvent(event);
}
