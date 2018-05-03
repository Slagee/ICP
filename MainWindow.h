#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QtGui>
#include <QFileDialog>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "ui_MainWindow.h"
#include "Block/AbstractBlock.h"
#include "Type/RegisterTypes.h"

class AbstractBlock;

namespace Ui { class MainWindow; }

/*!
 * \brief Třída reprezentující hlavní okno programu.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor hlavního okna programu.
     * \param parent - ukazatel na rodiče (widget)
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*!
     * \brief Metoda pro zjištění šířky toolbaru pro bloky.
     * \return Vrací šířku toolbaru pro bloky
     */
    int getToolbarWidth();

    /*!
     * \brief Metoda pro zjištění výšky menu.
     * \return Vrací výšku menu.
     */
    int getMenuHeight();

    /*!
     * \brief Metoda pro zjištění vnitřního odsazení toolbaru pro bloky.
     * \return Vrací velikost vnitřního odsazení toolbaru pro bloky
     */
    int getToolbarMargin();

    /*!
     * \brief Metoda pro zjištění, zdali je povoleno tahat dráty.
     * \return Vrací truu, pokud je, jinak false.
     */
    bool getWireEnabled();

private slots:
    /*!
     * \brief Zdířka pro kliknutí na menu New.
     */
    void on_actionNew_triggered();

    /*!
     * \brief Zdířka pro kliknutí na menu Calculate.
     */
    void on_actionCalculate_triggered();

    /*!
     * \brief Zdířka pro kliknutí na menu Step calculation.
     */
    void on_actionStep_Calculation_triggered();

    /*!
     * \brief Zdířka pro kliknutí na menu Help.
     */
    void on_actionHelp_triggered();

    /*!
     * \brief Zdířka pro kliknutí na menu Save.
     */
    void on_action_Save_triggered();

    /*!
     * \brief Zdířka pro kliknutí na menu Open.
     */
    void on_action_Open_triggered();

private:
    /*!
     * \brief TOOLBAR_WIDTH - konstanta pro nastavení sířky toolbaru pro bloky
     */
    const int TOOLBAR_WIDTH = 120;

    /*!
     * \brief TOOLBAR_HEIGHT - konstanta pro nastavení výšky položky toolbaru pro bloky
     */
    const int TOOLBAR_HEIGHT = 52;

    /*!
     * \brief MENU_HEIGHT - konstanta pro výšku menu
     */
    const int MENU_HEIGHT = 25;

    /*!
     * \brief TOP_MARGIN - konstanta pro odsazení od vrcholu okna
     */
    const int TOP_MARGIN = 30;

    /*!
     * \brief TOOLBAR_MARGIN - konstanta pro vnitřní odsazení toolbaru pro bloky
     */
    const int TOOLBAR_MARGIN = 6;

    /*!
     * \brief TOOLS_NOT_ACTIVE - konstanta pro nastavení, že tooly pro bloky nejsou aktivní
     */
    const int TOOLS_NOT_ACTIVE = 9999;

    /*!
     * \brief ui - ukazatel na GUI
     */
    Ui::MainWindow *ui;

    /*!
     * \brief scene - ukazatel na scénu
     */
    QGraphicsScene *scene;

    /*!
     * \brief tool - pro nastavení aktuálního nástroje pro tvorbu bloků
     */
    int tool = TOOLS_NOT_ACTIVE;

    /*!
     * \brief toolsForBlocks - ukazatel na toolbar pro bloky
     */
    QToolBar *toolsForBlocks;

    /*!
     * \brief stepCalculations - ukazatel na toolbar pro krokování
     */
    QToolBar *stepCalculations;

    /*!
     * \brief Metoda pro spočítání bloků na scéně.
     * \return Vrací počet bloků na scéně.
     */
    int countBlocks();

    /*!
     * \brief Metoda pro zjištění ukazatele na blok na daném indexu.
     * \param index - index bloku
     * \return Vrací ukazatel na blok.
     */
    AbstractBlock *getBlock(int index);

    /*!
     * \brief Metoda pro zjištění cyklů.
     * \return Vrací true, pokud se ve schématu nachází cykly, jinak false.
     */
    bool findCycles();

    /*!
     * \brief Metoda pro zjištění, zdali se blo nachází v cyklu.
     * \param block - ukazatel na blok, o kterém chceme zjistit, zdali se nachází v cyklu
     * \return Vrací true, pokud se blok nachází v cyklu, jinak false.
     */
    bool isInCycle(AbstractBlock *block);

    /*!
     * \brief Metoda pro zjištění zdali se blok nachází ve větvi.
     * \param block - ukazatel na blok, o kterém nás informace zajímá
     * \param branch - větev, o které informaci zjišťujeme
     * \return Vrací true pokud se blok ve větvi nachází, jinak false.
     */
    bool isBlockInBranch(AbstractBlock *block, AbstractBlock *branch);

    /*!
     * \brief Metoda pro zjištění, zdali je blok koncovým blokem.
     * \param block - ukazatel na blok, o kterém nás informace zajímá
     * \return Vrací true pokus je blok koncovým blokem, jinak false.
     */
    bool isEndBlock(AbstractBlock *block);

    /*!
     * \brief Medota pro provedení výpočtu schámatu.
     */
    void calculate();

    /*!
     * \brief Metoda pro zjištění, zdali je blok připraven k výpočtu.
     * \param block - ukazatel na blok, o kterém nás informace zajímá
     * \return Vrací true pokud je blok připraven k výpočtu, jinak false.
     */
    bool readyForCalculation(AbstractBlock *block);

    /*!
     * \brief Metoda pro nastavení všech bloků jako nepropočítaných.
     */
    void setBlocksNotCalculated();

    /*!
     * \brief Metoda pro zjištění, zdali jsou všechny vstupní porty bez drátu vyplněné.
     * \return Vrací true pokud jsou všechny vstupní porty vyplněné, jinak false.
     */
    bool checkWirelessInPorts();

    /*!
     * \brief Metoda pro poslání hodnot podráte.
     * \param block - ukazatel na blok, z něhož se mají hodnoty poslat dál
     */
    void sendResultsByWire(AbstractBlock *block);

    /*!
     * \brief Metoda pro vytvoření toolbaru pro krokování.
     */
    void createToolbarForStelCalculations();

    /*!
     * \brief Metoda pro odstranění toolbaru pro krokování.
     * \param stepCalculations - ukazatel na toolbar pro krokování
     */
    void removeToolbarForStelCalculations(QToolBar *stepCalculations);

    /*!
     * \brief Metoda pro provedení dálšího kroku při krokování.
     */
    void nextStep();

    /*!
     * \brief Metoda pro dokončení výpočtu při krokování.
     */
    void finishCalculations();

    /*!
     * \brief Metoda pro ukončení krokování.
     */
    void endCalculations();

    /*!
     * \brief Metoda pro nastavení bloků pro krokování.
     * \param color - barva, na kterou se mají bloky nastavit
     */
    void setBlocksForStepCalculations(QColor color);

    /*!
     * \brief Metoda pro zjištění dalšího bloku pro krokování.
     * \return Vrací ukazatel na další blok pro krokování
     */
    AbstractBlock *getNextBlockForStepCalculations();

    /*!
     * \brief Metoda pro nastavení barvy posledního propočítaného bloku.
     */
    void setPreviousLastCalculatedBlockColor();

    /*!
     * \brief Metoda pro nastavení bloku pro další krok, při krokování.
     */
    void setNextBlockForStepCalculations();

    /*!
     * \brief Metoda pro zjištění, zdali již není konec krokování.
     * \return Vrací true pokud je konec krokování, jinak false.
     */
    bool checkEndOfStepCalculations();

    /*!
     * \brief Metoda pro nastavení aktivního nástroje pro tvorbu bloků.
     * \param index - index nástroje pro tvorbu bloků
     */
    void setTool(int index);

    /*!
     * \brief Metoda pro vytvoření bloku.
     * \param index - index nástroje pro tvorbu bloků
     */
    void createBlock(int index);

    /*!
     * \brief Metoda pro vytvoření toolbaru pro bloky.
     */
    void createToolbarForBlocks();

    /*!
     * \brief Metoda pro povolení zakázaných věcí pro krokování.
     */
    void enableAfterStepCalculations();

    /*!
     * \brief Metoda pro zakázání věcí pro krokování.
     */
    void disableForStepCalculations();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
