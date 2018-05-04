/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QGraphicsItemGroup>

#include "Port/Port.h"
#include "Block/FillValuesBlock.h"

class Port;

/*!
 * \brief Abstraktní třída reprezetující jednotlivé bloky.
 */
class AbstractBlock : public QGraphicsItemGroup {
private:
    /*!
     * \brief TOP_BOTTOM_SPACING - konstanta pro úpravu pozic portů na blok
     */
    const int TOP_BOTTOM_SPACING = -5;

    /*!
     * \brief LABELS_SPACING - konstanta pro nastavení velikosti odsazení popisků portů od kraje těla bloků
     */
    const int LABELS_SPACING = 3;

    /*!
     * \brief BLOCK_NAME_SIZE - konstanta pro nastavení velikosti fontu názvu bloků
     */
    const int BLOCK_NAME_SIZE = 14;

    /*!
     * \brief BLOCK_LABEL_SIZE - konstanta pro nastavení velikosti fontu popisků portů
     */
    const int BLOCK_LABEL_SIZE = 10;

    /*!
     * \brief BLOCK_NAME_BOLD - konstanta pro nastavení, že jméno bloků bude/nebude tučně
     */
    const bool BLOCK_NAME_BOLD = true;

    /*!
     * \brief BLOCK_TEXT_FONT - konstanta pro nastavení fontu pro texty na blocích
     */
    const QString BLOCK_TEXT_FONT = "Sans Serif";

    /*!
     * \brief BLOCK_BORDER_THICKNESS - konstanta pro nastavení šířky ohraničení bloků
     */
    const int BLOCK_BORDER_THICKNESS = 2;

    /*!
     * \brief DEFAULT_BLOCK_COLOR - konstanta pro nastavení výchozí barvy ohraničení bloků
     */
    const QColor DEFAULT_BLOCK_COLOR = Qt::black;

    /*!
     * \brief ACTUAL_BLOCK_COLOR - konstanta pro nastavení barvy ohraničení těl bloků pro aktuální blok
     */
    const QColor ACTUAL_BLOCK_COLOR = Qt::yellow;

    /*!
     * \brief NOT_CALCULATED_BLOCK_COLOR - konstanta pro nastavení barvy ohraničení těl bloků pro nepropočítané bloky
     */
    const QColor NOT_CALCULATED_BLOCK_COLOR = Qt::red;

    /*!
     * \brief CALCULATED_BLOCK_COLOR - konstanta pro nastavení barvy ohraničení těl bloků pro propočítané bloky
     */
    const QColor CALCULATED_BLOCK_COLOR = Qt::green;

    /*!
     * \brief LAST_CALCULATED_BLOCK_COLOR - konstanta pro nastavení barvy ohraničení těl bloků pro poslední propočítaný blok
     */
    const QColor LAST_CALCULATED_BLOCK_COLOR = Qt::blue;

    /*!
     * \brief calculated - informace, zdali blok je/není propočítaný
     */
    bool calculated = false;

    /*!
     * \brief blockBorderColor - aktuální barva ohraničení těla bloku
     */
    QColor blockBorderColor = Qt::black;

public:
    /*!
     * \brief startX - prvnotní x-ová souřadnice bloku po vytvoření
     */
    int startX = 0;

    /*!
     * \brief startY - prvnotní y-nová souřadnice bloku po vytvoření
     */
    int startY = 0;

    /*!
     * \brief myParent - ukazatel na rodiče (scénu)
     */
    QGraphicsScene *myParent = nullptr;

    /*!
     * \brief Metoda pro vykreslování těla bloku.
     * \param painter - ukazatel na painter, který bude provádět vykreslování
     * \param options - ukazatel na nastavení, není využíváno
     * \param widget - ukazatel na widget, není využíváno
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    /*!
     * \brief Metoda pro vytvoření oblasti ohraničující tělo bloku.
     * \return Vrací obdelník ohraničující tělo bloku.
     */
    QRectF boundingRect() const;

    /*!
     * \brief Metoda pro zjištění šířky těla bloku.
     * \return Vrací šířku těla bloku.
     */
    virtual int getBlockWidth() const = 0;

    /*!
     * \brief Metoda pro zjištění výšky těla bloku.
     * \return Vrací výšku těla bloku.
     */
    virtual int getBlockHeight() const = 0;

    /*!
     * \brief Metoda pro zjištění počtu vstupních portů bloku.
     * \return Vrací počet vstupních portů bloku.
     */
    virtual int getInPortsCount() const = 0;

    /*!
     * \brief Metoda pro zjištění počtu výstupních portů bloku.
     * \return Vrací počet výstupních portů bloku.
     */
    virtual int getOutPortsCount() const = 0;

    /*!
     * \brief Metoda pro zjištění jména třídy bloku bloku.
     * \return Vrací jméno třídy bloku.
     */
    virtual QString getBlockClassName() const = 0;

    /*!
     * \brief Metoda pro zjištění jména (popisu) těla bloku.
     * \return Vrací jméno (popis) těla bloku.
     */
    virtual QString getBlockName() const = 0;

    /*!
     * \brief Metoda pro zjištění popisku vstupního portu bloku.
     * \param index - index vstupního portu bloku
     * \return Vrací popisek vstupního portu bloku.
     */
    virtual QString getInPortLabel(int index) const = 0;

    /*!
     * \brief Metoda pro zjištění popisku výstupního portu bloku.
     * \param index - index výstupního portu bloku
     * \return Vrací popisek výstupního portu bloku.
     */
    virtual QString getOutPortLabel(int index) const = 0;

    /*!
     * \brief Metoda pro zjištění typu dat na vstupním portu bloku.
     * \param index - index vstupního portu bloku
     * \return Vrací typ dat na vstupním portu bloku.
     */
    virtual QString getInPortDataType(int index) const = 0;

    /*!
     * \brief Metoda pro zjištění typu dat na výstupním portu bloku.
     * \param index - index výstupního portu bloku
     * \return Vrací typ dat na výstupním portu bloku.
     */
    virtual QString getOutPortDataType(int index) const = 0;

    /*!
     * \brief Metoda provede výpočet bloku.
     */
    virtual void doCalculation() = 0;

    /*!
     * \brief Metoda pro zjištění ukazatele na výstupní port bloku.
     * \param index - index výstupního portu bloku
     * \return Vrací ukazatel na výstupní port bloku.
     */
    Port *getOutPort(int index);

    /*!
     * \brief Metoda pro zjištění ukazatele na vstupní port bloku.
     * \param index - index vstupního portu bloku
     * \return Vrací ukazatel na vstupní port bloku.
     */
    Port *getInPort(int index);

    /*!
     * \brief Metoda pro nastavení, že blok je/není propočítán.
     * \param value - true (je propočítán), false (není propočítán)
     */
    void setCalculated(bool value);

    /*!
     * \brief Metoda pro zjištění, zdali byl blok propočítán.
     * \return Vrací informaci, zdali byl blok propočítán.
     */
    bool getCalculated();

    /*!
     * \brief Metoda pro nastavení barvy ohraničení těla bloku.
     * \param color - barva ohraničení bloku
     */
    void setBlockBorderColor(QColor color);

    /*!
     * \brief Metoda pro zjištění barvy ohraničení těla bloku.
     * \return Vrací barvu ohraničení těla bloku.
     */
    QColor getBlockBorderColor();

    /*!
     * \brief Metoda pro zjištění výchozí barvy ohraničení těla bloku.
     * \return Vrací výchozí barvu ohraničení těla bloku.
     */
    QColor getDefaultBorderColor();

    /*!
     * \brief Metoda pro zjištění barvy ohraničení těla bloku pro aktuální blok.
     * \return Vrací barvu ohraničení těla bloku pro aktuální blok.
     */
    QColor getActualBorderColor();

    /*!
     * \brief Metoda pro zjištění barvy ohraničení těla bloku pro nepropočítaný blok.
     * \return Vrací barvu ohraničení těla bloku pro nepropočítaný blok.
     */
    QColor getNotCalculatedBorderColor();

    /*!
     * \brief Metoda pro zjištění barvy ohraničení těla bloku pro propočítaný blok.
     * \return Vrací barvu ohraničení těla bloku pro propočítaný blok.
     */
    QColor getCalculatedBorderColor();

    /*!
     * \brief Metoda pro zjištění barvy ohraničení těla bloku pro poslední propočítaný blok.
     * \return Vrací barvu ohraničení těla bloku pro poslední propočítaný blok.
     */
    QColor getLastCalculatedBorderColor();

    /*!
     * \brief Metoda pro sestrojení bloku.
     */
    void constructBlock();

protected:
    /*!
     * \brief Metoda pro zpracování dvojkliku na blok.
     * \param event - ukazatel na událost
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief Metoda pro zpracování kliknutí na blok.
     * \param event - ukazatel na událost
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ABSTRACTBLOCK_H
