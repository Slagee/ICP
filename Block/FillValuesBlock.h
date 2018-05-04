/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef FILLVALUESBLOCK_H
#define FILLVALUESBLOCK_H

#include "ui_FillValues.h"
#include "AbstractBlock.h"

class AbstractBlock;

/*!
 * \brief Třída reprezentující okno pro vyplenění hodnot vstupních portů celého bloku.
 */
class FillValuesBlock : public QDialog {
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor okna pro vyplenění hodnot vstupních portů celého bloku.
     * \param someBlock - ukazatel na blok, jehož hodnoty má uživatel vyplnit
     * \param parent - ukazatel na widget, který okno volá
     */
    explicit FillValuesBlock(AbstractBlock *someBlock, QWidget *parent = 0);
    ~FillValuesBlock();

private slots:
    /*!
     * \brief Zdířka pro kliknutí na "OK" tlačítko.
     */
    void on_pushButton_clicked();

private:
    /*!
     * \brief ui - ukazatel na GUI
     */
    Ui::FillValues *ui;

    /*!
     * \brief parentBlock - ukazatel na blok, pro který má uživatel vyplnit hodnoty vstupních portů
     */
    AbstractBlock *block;
};

#endif // FILLVALUESBLOCK_H
