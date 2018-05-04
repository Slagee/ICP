/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef PORT_H
#define PORT_H

#include <QGraphicsSceneMouseEvent>
#include <QtWidgets>
#include <QMessageBox>

#include "Port/FillValuesPort.h"
#include "Wire/Wire.h"

class AbstractBlock;
class AbstractType;
class Wire;

/*!
 * \brief Třída reprezentující port.
 */
class Port : public QGraphicsItem {
private:
    /*!
     * \brief PORT_RADIUS - konstanta pro nastavení poloměru portu
     */
    const int PORT_RADIUS = 7;

    /*!
     * \brief WIRELESS_UNSET_IN_PORT_COLOR - konstanta pro nastavení barvy vstupního portu bez drátu a bez vyplněných hodnot
     */
    const QColor WIRELESS_UNSET_IN_PORT_COLOR = Qt::red;

    /*!
     * \brief WIRELESS_SET_IN_PORT_COLOR - konstanta pro nastavení barvy vstupního portu bez drátu a s vyplněnýma hodnotama
     */
    const QColor WIRELESS_SET_IN_PORT_COLOR = Qt::green;

    /*!
     * \brief WIRELESS_OUT_PORT_COLOR - konstanta pro nastavení barvy výstupního portu bez drátu
     */
    const QColor WIRELESS_OUT_PORT_COLOR = Qt::blue;

    /*!
     * \brief WIRED_IN_OUT_PORT_COLOR - konstanta pro nastavení barvy portu s drátem
     */
    const QColor WIRED_IN_OUT_PORT_COLOR = Qt::black;

    /*!
     * \brief HOVER_IN_OUT_PORT_COLOR - konstanta pro nastavení barvy portu, nad kterým je myš
     */
    const QColor HOVER_IN_OUT_PORT_COLOR = Qt::yellow;

    /*!
     * \brief inPort - true (jedná se o vstupní port), false (jedná se o výstupní port)
     */
    bool inPort = false;

    /*!
     * \brief onMouse - true (pokud se nad portem nachází kurzor), jinak false
     */
    bool onMouse = false;

    /*!
     * \brief dragOver - true (pokud se přes port táhne drát), jinak false
     */
    bool dragOver = false;

    /*!
     * \brief id - unikátní id portu
     */
    int id;

    /*!
     * \brief dataType - ukazatel na instanci dat portu
     */
    AbstractType *dataType = nullptr;

    /*!
     * \brief isInCycle - slouží k detekci cyklů
     */
    bool isInCycle = false;

    /*!
     * \brief portWire - ukazatel na drát, který je v portu
     */
    Wire *portWire = nullptr;

public:
    /*!
     * \brief myParent - ukazatel na rodiče (blok)
     */
    AbstractBlock *myParent = nullptr;

    /*!
     * \brief Konstruktor portu.
     * \param dataTypeName - název typu dat portu
     * \param parent - ukazatel na rodiče (blok)
     */
    Port(QString dataTypeName, AbstractBlock *parent = 0);

    /*!
     * \brief Metoda pro vytvoření obdelníku ohraničujícího port
     * \return Vrací obdelník ohraničující port.
     */
    QRectF boundingRect() const;

    /*!
     * \brief Metoda pro vykreslování portu.
     * \param painter - ukazatel na painter, který bude provádět vykreslování
     * \param options - ukazatel na nastavení, není využíváno
     * \param widget - ukazatel na widget, není využíváno
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*!
     * \brief Metoda pro zjištění poloměru portu.
     * \return Vrací poloměr portu.
     */
    int getPortRadius();

    /*!
     * \brief Metoda pro nastavení, zdali se jedná o vstupní port.
     * \param value - true (jedná se o vsupní port), jinak false
     */
    void setInPort(bool value);

    /*!
     * \brief Metoda pro zjištění, zdali je jedná o vstupní port.
     * \return Vrací true pokud se jedná o vstupní port, jinak false.
     */
    bool getInPort();

    /*!
     * \brief Metoda pro zjištění id portu.
     * \return Vrací id portu.
     */
    int getPortID();

    /*!
     * \brief Metoda pro zjištění ukazatele na na drát v portu.
     * \return Vrací ukazatel na drát v portu.
     */
    Wire *getWire();

    /*!
     * \brief Metoda pro nastavení drátu v portu.
     * \param Ukazatel na drát v portu.
     */
    void setWire(Wire *value);

    /*!
     * \brief Metoda pro zjištění ukazatele na instanci dat portu.
     * \return Vrací ukazatel na instanci dat portu.
     */
    AbstractType *getDataType();

    /*!
     * \brief Metoda pro vytvoření textu tooltipu portu.
     * \return Vrací text tooltipu portu.
     */
    QString createToolTip();

    /*!
     * \brief Metoda pro nastavení id portu.
     * \param value - hodnota id portu
     */
    void setPortID(int value);

    /*!
     * \brief Metoda pro spočítání bloků na scéně.
     * \return Vrací počet bloků na scéně.
     */
    int countBlocks();

    /*!
     * \brief Metoda pro zjištění ukazatele na blok.
     * \param index - index bloku.
     * \return Vrací ukazatel na blok.
     */
    AbstractBlock *getBlock(int index);

    /*!
     * \brief Metoda pro zjištění následujícího dalšího id portu.
     * \param value - true (nastavení čítače id), false (vrací další id v pořadí)
     * \return Vrací id pro další port.
     */
    int getNextId(bool value = false);

    /*!
     * \brief Metoda pro zjištění, jak ma nastavenou proměnnou pro detekci cyklů.
     * \return Vrací true (pokud byl blok navštíven), jinak false
     */
    bool getIsInCycle();

    /*!
     * \brief Metoda pro nastavení proměnné pro detekci cyklů.
     * \param value - hodnota, na jakou má být proměnná nastavena
     */
    void setIsInCycle(bool value);

protected:
    /*!
     * \brief Metoda pro zpracování vstupu kurzoru při táhnutí drátu.
     * \param event - ukazatel na událost
     */
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

    /*!
     * \brief Metoda pro zpracování opuštění kurzoru při táhnutí drátu.
     * \param event - ukazatel na událost
     */
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

    /*!
     * \brief Metoda pro zpracování ukončení táhnutí drátu.
     * \param event - ukazatel na událost
     */
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    /*!
     * \brief Metoda pro zpracování vstupu kurzoru nad port.
     * \param event - ukazatel na událost
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /*!
     * \brief Metoda pro zpracování opuštění kurzoru z portu.
     * \param event - ukazatel na událost
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    /*!
     * \brief Metoda pro zpracování kliknutí na port.
     * \param event - ukazatel na událost
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief Metoda pro zpracování porhybu kurzoru nad portem.
     * \param event - ukazatel na událost
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief Metoda pro zpracování odkliknutí na portu.
     * \param event - ukazatel na událost
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PORT_H
