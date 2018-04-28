#ifndef WIRE_H
#define WIRE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

#include "mainwindow.h"

class port;

// trida pro drat - zacatek (start) ma vzdy v in-portu a konec (end) v out-portu
class wire : public QGraphicsItem  {
private:
    // ukazatele na in-port/out-port
    port *startPort = nullptr;
    port *endPort = nullptr;

    // detekce zdali je port z porto do portu nebo se teprve tahne mysi
    bool dragFinished = false;

    // promenne pro posun zacatku/konce dratu pri pohybu bloku s in-portem/out-portem
    int shiftStartX;
    int shiftStartY;
    int shiftEndX;
    int shiftEndY;

public:
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

    // metoda pro nastaveni, ze bylo tahnuti dratu ukonceno
    void setDragFinished(bool value);

    // metody pro nastaveni posunu zacatku/konce dratu
    void setShiftStartX(int value);
    void setShiftStartY(int value);
    void setShiftEndX(int value);
    void setShiftEndY(int value);
};
#endif // WIRE_H