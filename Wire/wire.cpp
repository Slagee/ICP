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

    return QRectF(0, 0, myParent->width(), myParent->height());
/* kdyz se da bounding rect presne, tak se pri rychlych poybech zustava stara cara...
    int x1, x2, y1, y2;
    if (startPort != nullptr && endPort != nullptr) {
        x1 = this->startPort->x() + shiftStartX + this->startPort->getPortRadius();
        y1 = this->startPort->y() + shiftStartY + this->startPort->getPortRadius();
        x2 = this->endPort->x() + shiftEndX + this->endPort->getPortRadius();
        y2 = this->endPort->y() + shiftEndY + this->endPort->getPortRadius();
     } else if (!dragFinished) {

        MainWindow *w = qobject_cast<MainWindow *>(myParent->parent());
        QPoint mouse = w->mapFromGlobal(QCursor::pos());

        if (startPort != nullptr) {
            x1 = this->startPort->x() + shiftStartX + this->startPort->getPortRadius();
            y1 = this->startPort->y() + shiftStartY + this->startPort->getPortRadius();
            x2 = mouse.x() - w->toolBarWidth;
            y2 = mouse.y() - w->menuHeight;
        } else if (endPort != nullptr) {
            x1 = mouse.x() - w->toolBarWidth;
            y1 = mouse.y() - w->menuHeight;
            x2 = this->endPort->x() + shiftEndX + this->endPort->getPortRadius();
            y2 = this->endPort->y() + shiftEndY + this->endPort->getPortRadius();
        }
    }

    int x,y,wr,hr;

    (x1 < x2) ? x = x1 - 10 : x = x2 - 10;
    (y1 < y2) ? y = y1 - 10 : y = y2 - 10;

    wr = abs(x1 - x2) + 20;
    hr = abs(y1 - y2) + 20;
    return QRectF(x,y,wr,hr);
*/
}
void wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    if (startPort != nullptr && endPort != nullptr) {
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
