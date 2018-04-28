#ifndef WIRE_H
#define WIRE_H

#include <QPainter>
#include <QLine>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>

#include "Port/port.h"
class port;

class wire : public QGraphicsItem  {
private:
    port *startPort;
    port *endPort;

public:
    int shiftStartX;
    int shiftStartY;
    int shiftEndX;
    int shiftEndY;
    bool dragFinished;
    QGraphicsScene *myParent;

    wire(int x1, int y1, int x2, int y2, QGraphicsScene *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setStartPort(port *port);
    void setEndPort(port *port);
    port *getStartPort();
    port *getEndPort();
};
#endif // WIRE_H
