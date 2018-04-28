#ifndef PORT_H
#define PORT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtWidgets>
#include <QColor>
#include <QDragEnterEvent>

#include "../Block/abstractBlock.h"
#include "Wire/wire.h"

class abstractBlock;
class wire;

class port : public QGraphicsItem {
private:
    const int PORT_RADIUS = 7;
    const QColor WIRELESS_UNSET_IN_PORT_COLOR = Qt::red;
    const QColor WIRELESS_SET_IN_PORT_COLOR = Qt::green;
    const QColor WIRELESS_OUT_PORT_COLOR = Qt::blue;
    const QColor WIRED_IN_OUT_PORT_COLOR = Qt::black;
    const QColor HOVER_IN_OUT_PORT_COLOR = Qt::yellow;
    bool onMouse;
    bool pressed;
    bool dragOver;
    abstractBlock *myParent;

public:
    int number;
    bool inPort;
    wire *portWire ;
    port(abstractBlock *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getPortRadius();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // QGraphicsItem interface
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PORT_H
