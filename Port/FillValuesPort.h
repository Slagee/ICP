#ifndef FILLVALUESPORT_H
#define FILLVALUESPORT_H


#include <QGroupBox>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ui_FillValues.h"
#include "Port/Port.h"

class Port;
class AbstractBlock;

/*!
 * \brief Třída reprezentující okno pro vyplenění hodnot vstupního portu.
 */
class FillValuesPort : public QDialog {
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor okna pro vyplenění hodnot vstupních portů celého bloku.
     * \param parentPort - ukazatel na vstupní port, jehož hodnoty má uživatel vyplnit
     * \param parent - ukazatel na widget, který okno volá
     */
    explicit FillValuesPort(Port *parentPort, QWidget *parent = 0);
    ~FillValuesPort();

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
    * \brief blockPort - ukazatel na vstupní port, pro který má uživatel vyplnit hodnoty
    */
   Port *blockPort;
};

#endif // FILLVALUESPORT_H
