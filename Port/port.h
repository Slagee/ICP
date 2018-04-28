#ifndef PORT_H
#define PORT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtWidgets>
#include <QColor>
#include <QDragEnterEvent>

#include "Type/abstractType.h"
#include "Type/onedecimalnumber.h"
#include "Type/twodecimalnumbers.h"
#include "Type/threedecimalnumbers.h"
#include "Wire/wire.h"

class abstractBlock;
class abstractType;
class wire;

// trida pro port
class port : public QGraphicsItem {
private:
    // konstanty pro nastaveni velikosti portu a barev portu
    const int PORT_RADIUS = 7;
    const QColor WIRELESS_UNSET_IN_PORT_COLOR = Qt::red;
    const QColor WIRELESS_SET_IN_PORT_COLOR = Qt::green;
    const QColor WIRELESS_OUT_PORT_COLOR = Qt::blue;
    const QColor WIRED_IN_OUT_PORT_COLOR = Qt::black;
    const QColor HOVER_IN_OUT_PORT_COLOR = Qt::yellow;

    // informace zdali se jedna o in-port
    bool inPort = false;

    // promenne pro detekci ze se nad nim nachazi mys nebo ze se pres nej neco pretahuje
    bool onMouse = false;
    bool dragOver = false;

public:

    // ukazatel na drat
    wire *portWire = nullptr;

    // ukazatel na typ s daty
    abstractType *dataType = nullptr;

    // ukazatel na otce
    abstractBlock *myParent = nullptr;

    // konstruktor
    port(abstractBlock *parent = 0);

    // pro prostor portu
    QRectF boundingRect() const;

    // pro kresleni portu
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // pro zjisteni vleikosti portu
    int getPortRadius();

    //metody pro nastaveni vstupniho portu a zjisteni zdali se jedno o in-port/out-port
    void setInPort(bool value);
    bool getInPort();

protected:

    // prace s udalostmi...
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // PORT_H
