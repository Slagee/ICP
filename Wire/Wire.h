#ifndef WIRE_H
#define WIRE_H

#include <QPainter>
#include <QGraphicsLineItem>
#include <QDebug>

#include "MainWindow.h"

class Port;

/*!
 * \brief Třída reprezentující drát.
 */
class Wire : public QGraphicsLineItem  {
private:
    /*!
     * \brief WIRE_THICKNESS - konstanta pro nasatvení tloušťky drátu.
     */
    const int WIRE_THICKNESS = 3;

    /*!
     * \brief shiftStartX - nastavení posunu x-ové souřadnice začátku drátu oproti počátešní poloze
     */
    int shiftStartX;

    /*!
     * \brief shiftStartY - nastavení posunu y-nové souřadnice začátku drátu oproti počátešní poloze
     */
    int shiftStartY;

    /*!
     * \brief shiftEndX - nastavení posunu x-ové souřadnice konce drátu oproti počátešní poloze
     */
    int shiftEndX;

    /*!
     * \brief shiftEndY - nastavení posunu y-nové souřadnice konce drátu oproti počátešní poloze
     */
    int shiftEndY;

    /*!
     * \brief dragFinished - true (pokud je drát natažený), false (pokud se táhne)
     */
    bool dragFinished = false;

public:
    /*!
     * \brief startPort - ukazatel na vstupní port
     */
    Port *startPort = nullptr;

    /*!
     * \brief endPort - ukazatel na výstupní port
     */
    Port *endPort = nullptr;

    /*!
     * \brief myParent - ukazatel na rodiče (scéna)
     */
    QGraphicsScene *myParent;

    /*!
     * \brief Konstruktor pro drát.
     * \param parent - ukazatel na rodiče (scéna)
     */
    Wire(QGraphicsScene *parent = 0);

    /*!
     * \brief Metoda pro vytvoření oblastni pro drát.
     * \return Vrací obdelník pro drát.
     */
    QRectF boundingRect() const;

    /*!
     * \brief Metoda pro vykreslování drát.
     * \param painter - ukazatel na painter, který bude provádět vykreslování
     * \param options - ukazatel na nastavení, není využíváno
     * \param widget - ukazatel na widget, není využíváno
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*!
     * \brief Metoda pro nastavení portu na začátku drátu.
     * \param port - ukazatel na port na začátku drátu
     */
    void setStartPort(Port *port);

    /*!
     * \brief Metoda pro nastavení portku na konci drátu.
     * \param port - ukazatel na port na konci drátu
     */
    void setEndPort(Port *port);

    /*!
     * \brief Metoda pro zjištění portu na začátku drátu.
     * \return Vrací ukazatel na port na začátku drátu.
     */
    Port *getStartPort();

    /*!
     * \brief Metoda pro zjištění portu na konci drátu.
     * \return Vrací ukazatel na port na konci drátu.
     */
    Port *getEndPort();

    /*!
     * \brief Metoda pro zjištění druhého portu, který je spojený s drátem.
     * \param somePort - ukazatel na první port, se kterým je drát spojen
     * \return Vrací ukazatel na druhý port, se kterým je drát spojen.
     */
    Port *getOtherPort(Port *somePort);

    /*!
     * \brief Metoda pro nastavení, zdali bylo tažení drátu dokončeno.
     * \param value - true (pokud byl drát dotažen), jinak false
     */
    void setDragFinished(bool value);

    /*!
     * \brief Metoda pro nastavení posunu x-ové souřadnice začátku drátu oproti počátešní poloze.
     * \param value - o kolik se posunula x-ová souřadnice začátku drátu oproti počáteční poloze
     */
    void setShiftStartX(int value);

    /*!
     * \brief Metoda pro nastavení posunu y-nové souřadnice začátku drátu oproti počátešní poloze.
     * \param value - o kolik se posunula y-nová souřadnice začátku drátu oproti počáteční poloze
     */
    void setShiftStartY(int value);

    /*!
     * \brief Metoda pro nastavení posunu x-ové souřadnice konce drátu oproti počátešní poloze.
     * \param value - o kolik se posunula x-ová souřadnice konce drátu oproti počáteční poloze
     */
    void setShiftEndX(int value);

    /*!
     * \brief Metoda pro nastavení posunu y-nové souřadnice konce drátu oproti počátešní poloze.
     * \param value - o kolik se posunula y-nová souřadnice konce drátu oproti počáteční poloze
     */
    void setShiftEndY(int value);

protected:
    /*!
     * \brief Metoda pro zpracování vstupu kurzoru nad drát.
     * \param event - ukazatel na událost
     */
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

};
#endif // WIRE_H
