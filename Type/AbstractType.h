#ifndef ABSTRACTTYPE_H
#define ABSTRACTTYPE_H

#include <QString>
#include <QGraphicsItem>
#include <QMetaType>
#include <QDebug>

class oneDecimalNumber;
class twoDecimalNumbers;
class threeDecimalNumbers;
class Port;

/*!
 * \brief Abstraktní třída reprezentující typy portů bloků
 */
class AbstractType {
private:
    /*!
     * \brief valuesSet - true (pokud jsou honoty nastavené), jinak false
     */
    bool valuesSet = false;

public:
    /*!
     * \brief myParent - ukazatel na rodiče (port)
     */
    Port *myParent = nullptr;

    /*!
     * \brief Metoda pro zjištění, zdali jsou nastavené hodnoty.
     * \return Vrací true pokud jsou hodnoty nastavené, jinak false.
     */
    bool getValuesSet();

    /*!
     * \brief Metoda pro nastavení, zdali jsou hodnoty nastavené.
     * \param value - true (hodnoty jsou nastavené), jinak  false
     */
    void setValuesSet(bool value);

    /*!
     * \brief Metoda pro nastavení ukazatele na rodiče (port).
     * \param parent - ukazatel na rodiče (port)
     */
    void setMyParent(Port *parent);

    /*!
     * \brief Metoda pro zjištění hodnoty na indexu.
     * \param index - index hodnoty na portu
     * \return Vrací hondotu na zadaném indexu.
     */
    virtual double getValue(int index) = 0;

    /*!
     * \brief Metoda pro nastavení hodnoty na indexu.
     * \param index - index, na kterém se má hodnota uložit
     * \param newValue - hodnota, která se má uložit
     */
    virtual void setValue(int index, double newValue) = 0;

    /*!
     * \brief Metoda pro zjištění počtu hodnot na portu.
     * \return Vrací počet hodnot na portu.
     */
    virtual int getValuesLength() = 0;

    /*!
     * \brief Metoda pro zjištění jména typu portu.
     * \return Vrací jméno typu portu.
     */
    virtual QString getType() = 0;

    /*!
     * \brief Metoda pro zjištění názvu hodnoty portu na indexu.
     * \param index - index hodnoty.
     * \return Vrací název hodnoty portu na idndexu.
     */
    virtual QString getValueName(int index) = 0;
};

#endif // ABSTRACTTYPE_H
