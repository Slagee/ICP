/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef ADDER1W1A2W1TO1W1A2W2A3W3_H
#define ADDER1W1A2W1TO1W1A2W2A3W3_H

#include "Block/AbstractBlock.h"

class AbstractBlock;

/*!
 * \brief Třída reprezentující bloky Adder1w1a2w1to1w1a2w2a3w3
 */
class Adder1w1a2w1to1w1a2w2a3w3 : public AbstractBlock {
private:
    /*!
     * \brief BLOCK_WIDTH - konstanta pro nastavení šířky těla bloku
     */
    const int BLOCK_WIDTH = 120;

    /*!
     * \brief BLOCK_HEIGHT - konstanta pro nastavení výšky těla bloku
     */
    const int BLOCK_HEIGHT = 65;

    /*!
     * \brief IN_PORTS_COUNT - konstanta pro nastavení počtu vstupních portů bloku
     */
    const static int IN_PORTS_COUNT = 2;

    /*!
     * \brief IN_PORTS_LABELS[] - konstanta pro nastavení popisků vstupních potrů bloku
     */
    const QString IN_PORTS_LABELS[IN_PORTS_COUNT] = {"1.1", "2.1"};

    /*!
     * \brief IN_PORTS_DATA_TYPES[] - konstanta pro nastavení typů dat vstupních potrů bloku
     */
    const QString IN_PORTS_DATA_TYPES[IN_PORTS_COUNT] = {"One Decimal Number", "One Decimal Number"};

    /*!
     * \brief OUT_PORTS_COUNT - konstanta pro nastavení počtu výstupních portů bloku
     */
    const static int OUT_PORTS_COUNT = 3;

    /*!
     * \brief OUT_PORTS_LABELS[] - konstanta pro nastavení popisků výstupních potrů bloku
     */
    const QString OUT_PORTS_LABELS[OUT_PORTS_COUNT] = {"1.1", "2.2", "3.3"};

    /*!
     * \brief OUT_PORTS_DATA_TYPES[] - konstanta pro nastavení typů dat výstupních potrů bloku
     */
    const QString OUT_PORTS_DATA_TYPES[OUT_PORTS_COUNT] = {"One Decimal Number", "Two Decimal Numbers", "Three Decimal Numbers"};

    /*!
     * \brief BLOCK_NAME - konstanta pro nastavení jména těla bloku
     */
    const QString BLOCK_NAME = "ADD";

    /*!
     * \brief BLOCK_CLASS_NAME - konstanta pro nastavení jména třídy bloku
     */
    const QString BLOCK_CLASS_NAME = "Adder1w1a2w1to1w1a2w2a3w3";

public:
    /*!
     * \brief Konstruktor pro blok Adder1w1a2w1to1w1a2w2a3w3
     * \param x - x-ová souřadnice umístění bloku
     * \param y - y-nová souřadnice umístění bloku
     * \param parent - ukazatel na rodiče (scénu)
     */
    Adder1w1a2w1to1w1a2w2a3w3(int x, int y, QGraphicsScene *parent = 0);

    /*!
     * \brief Metoda pro zjištění šířky těla bloku.
     * \return Vrací šířku těla bloku.
     */
    int getBlockWidth() const;

    /*!
     * \brief Metoda pro zjištění výšky těla bloku.
     * \return Vrací výšku těla bloku.
     */
    int getBlockHeight() const;

    /*!
     * \brief Metoda pro zjištění počtu vstupních portů bloku.
     * \return Vrací počet vstupních portů bloku.
     */
    int getInPortsCount() const;

    /*!
     * \brief Metoda pro zjištění počtu výstupních portů bloku.
     * \return Vrací počet výstupních portů bloku.
     */
    int getOutPortsCount() const;

    /*!
     * \brief Metoda pro zjištění jména třídy bloku bloku.
     * \return Vrací jméno třídy bloku.
     */
    QString getBlockClassName() const;

    /*!
     * \brief Metoda pro zjištění jména (popisu) těla bloku.
     * \return Vrací jméno (popis) těla bloku.
     */
    QString getBlockName() const;

    /*!
     * \brief Metoda pro zjištění popisku vstupního portu bloku.
     * \param index - index vstupního portu bloku
     * \return Vrací popisek vstupního portu bloku.
     */
    QString getInPortLabel(int index) const;

    /*!
     * \brief Metoda pro zjištění popisku výstupního portu bloku.
     * \param index - index výstupního portu bloku
     * \return Vrací popisek výstupního portu bloku.
     */
    QString getOutPortLabel(int index) const;

    /*!
     * \brief Metoda pro zjištění typu dat na vstupním portu bloku.
     * \param index - index vstupního portu bloku
     * \return Vrací typ dat na vstupním portu bloku.
     */
    QString getInPortDataType(int index) const;

    /*!
     * \brief Metoda pro zjištění typu dat na výstupním portu bloku.
     * \param index - index výstupního portu bloku
     * \return Vrací typ dat na výstupním portu bloku.
     */
    QString getOutPortDataType(int index) const;

    /*!
     * \brief Metoda provede výpočet bloku.
     */
    void doCalculation();
};

#endif // ADDER1W1A2W1TO1W1A2W2A3W3_H
