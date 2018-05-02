#ifndef WIRE_H
#define WIRE_H

#include <QPainter>
#include <QGraphicsLineItem>
#include <QDebug>

#include "mainwindow.h"

class port;

// trida pro drat - zacatek (start) ma vzdy v in-portu a konec (end) v out-portu
class wire : public QGraphicsLineItem  {
private:
    const int WIRE_THICKNESS = 3;

    // promenne pro posun zacatku/konce dratu pri pohybu bloku s in-portem/out-portem
    int shiftStartX;
    int shiftStartY;
    int shiftEndX;
    int shiftEndY;

    // detekce zdali je port z porto do portu nebo se teprve tahne mysi
    bool dragFinished = false;

public:
    // ukazatele na in-port/out-port
    port *startPort = nullptr;
    port *endPort = nullptr;

    // ukazatel na rodice --> scena
    QGraphicsScene *myParent;

    // konstruktor
    wire(QGraphicsScene *parent = 0);

    // pro vyrobeni boxu, ve kterem se ma drat nachazet (ktery bude vykreslovany matodou paint..)
    QRectF boundingRect() const;

    // pro kresleni dratu
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // metody pro nastaveni in-portu/out-portu
    void setStartPort(port *port);
    void setEndPort(port *port);

    // metody pro ziskani ukazatele na in-port/out-port
    port *getStartPort();
    port *getEndPort();
    port *getOtherPort(port *somePort);

    // metoda pro nastaveni, ze bylo tahnuti dratu ukonceno
    void setDragFinished(bool value);

    // metody pro nastaveni posunu zacatku/konce dratu
    void setShiftStartX(int value);
    void setShiftStartY(int value);
    void setShiftEndX(int value);
    void setShiftEndY(int value);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

};
#endif // WIRE_H
