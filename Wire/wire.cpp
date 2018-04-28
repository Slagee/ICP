#include "wire.h"
#include "mainwindow.h"

wire::wire(int x1, int y1, int x2, int y2, QGraphicsScene *parent) {
    shiftStartX = 0;
    shiftStartY = 0;
    shiftEndX = 0;
    shiftEndY = 0;

    dragFinished = false;
    startPort = nullptr;
    endPort = nullptr;
    myParent = parent;
}

QRectF wire::boundingRect() const {
/*
    if (endPort == nullptr & startPort == nullptr) {
        return QRectF(100, 100, 100, 100);

    } else if (endPort == nullptr) {
        return QRectF(this->startPort->x(), this->startPort->y(), 100, 100);
    } else {
        return QRectF(this->startPort->x(), this->startPort->y(), this->endPort->x() - this->startPort->x(), 200 );
    }


    if (startPort != nullptr && endPort != nullptr) {
        qDebug("tamec je 0 x 0 a  %f %f", qFabs(this->startPort->x() - this->endPort->x()), qFabs(this->startPort->y() - this->endPort->y()) );
        return QRectF(this->startPort->x() + shiftStartX, this->startPort->y() + shiftStartY, qFabs(this->startPort->x() - this->endPort->x()), qFabs(this->startPort->y() - this->endPort->y()));
    } else {
        return QRectF(0, 0, 0, 0);
    }
   */
    return QRectF(0,0, 1000,1000);
}
void wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    if (startPort != nullptr && endPort != nullptr) {
        QRectF portBox = boundingRect();
        painter->drawLine(this->startPort->x() + shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + shiftStartY + this->startPort->getPortRadius(), this->endPort->x() + shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + shiftEndY + this->endPort->getPortRadius());
     } else if (!dragFinished) {

        MainWindow *w = qobject_cast<MainWindow *>(myParent->parent());
        QPoint mouse = w->mapFromGlobal(QCursor::pos());

        if (startPort != nullptr) {
            painter->drawLine(this->startPort->x() + shiftStartX + this->startPort->getPortRadius(), this->startPort->y() + shiftStartY + this->startPort->getPortRadius(), mouse.x() - w->toolBarWidth, mouse.y() - w->menuHeight);
        } else if (endPort != nullptr) {
            painter->drawLine(mouse.x() - w->toolBarWidth, mouse.y() - w->menuHeight, this->endPort->x() + shiftEndX + this->endPort->getPortRadius(), this->endPort->y() + shiftEndY + this->endPort->getPortRadius());
        }
    }
}

void wire::setStartPort(port *port) { startPort = port; }

void wire::setEndPort(port *port) { endPort = port; }

port *wire::getStartPort() { return startPort; }

port *wire::getEndPort() { return endPort; }
