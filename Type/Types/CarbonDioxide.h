#ifndef CARBONDIOXIDE_H
#define CARBONDIOXIDE_H

#include "Type/AbstractType.h"

/*!
 * \brief Třída reprezentující typ CarbonDioxide
 */
class CarbonDioxide : public AbstractType {
private:  
    /*!
     * \brief TYPE_NAME - konstanta pro nastavení názvu typu"
     */
    const QString TYPE_NAME = "Carbon Dioxide";

    /*!
     * \brief NUMBER_OF_VALUES - konstanta pro nastavení počtu hodnot typu
     */
    const static int NUMBER_OF_VALUES = 1;

    /*!
     * \brief VALUES_NAMES[] - konstanta pro nastavení názvů hodnot typu
     */
    const QString VALUES_NAMES[NUMBER_OF_VALUES] = {"Carbon Dioxide"};

    /*!
     * \brief values[] - pole pro hodnoty typu
     */
    double values[NUMBER_OF_VALUES] = {0};

public:
    /*!
     * \brief Konstruktor typu CarbonDioxide.
     */
    CarbonDioxide();

    /*!
     * \brief Metoda pro zjištění hodnoty na indexu.
     * \param index - index hodnoty na portu
     * \return Vrací hondotu na zadaném indexu.
     */
    double getValue(int index);

    /*!
     * \brief Metoda pro nastavení hodnoty na indexu.
     * \param index - index, na kterém se má hodnota uložit
     * \param newValue - hodnota, která se má uložit
     */
    void setValue(int index, double newValue);

    /*!
     * \brief Metoda pro zjištění počtu hodnot na portu.
     * \return Vrací počet hodnot na portu.
     */
    int getValuesLength();

    /*!
     * \brief Metoda pro zjištění jména typu portu.
     * \return Vrací jméno typu portu.
     */
    QString getType();

    /*!
     * \brief Metoda pro zjištění názvu hodnoty portu na indexu.
     * \param index - index hodnoty.
     * \return Vrací název hodnoty portu na idndexu.
     */
    QString getValueName(int index);
};

#endif // CARBONDIOXIDE_H
