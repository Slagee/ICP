#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QtGui>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "Block/abstractBlock.h"
#include "Type/registrtypes.h"


namespace Ui { class MainWindow; }
class abstractBlock;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getToolbarWidth();
    int getMenuHeight();
    int getToolbarMargin();
    bool getWireEnabled();

private slots:
   // void on_actionadder_triggered();
    //void on_actionadder_hovered();
    //void on_actionsubtractor_hovered();
    //void on_actionsubtractor_triggered();
    void on_actionNew_triggered();
    void on_actionCalculate_triggered();
    void on_actionStep_Calculation_triggered();
   // void on_actionnapoveda_triggered();
    void on_actionHelp_triggered();

    void on_action_Save_triggered();

private:
    // promenned pro vyreseni spravne pozice sceny

    const int TOOLBAR_WIDTH = 120;
    const int TOOLBAR_HEIGHT = 50;
    const int MENU_HEIGHT = 25;
    const int TOP_MARGIN = 30;
    const int TOOLBAR_MARGIN = 6;
    const int TOOLS_NOT_ACTIVE = 9999;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int tool = TOOLS_NOT_ACTIVE;
    QToolBar *toolsForBlocks;
    QToolBar *stepCalculations;

    int countBlocks();
    abstractBlock *getBlock(int index);
    bool findCycles();
    bool isInCycle(abstractBlock *block);
    bool isBlockInBranch(abstractBlock *block, abstractBlock *branch);
    bool isEndBlock(abstractBlock *block);
    void calculate();
    bool readyForCalculation(abstractBlock *block);
    void setBlocksNotCalculated();
    bool checkWirelessInPorts();
    void sendResultsByWire(abstractBlock *block);
    QToolBar *createToolbarForStelCalculations();
    void removeToolbarForStelCalculations(QToolBar *stepCalculations);
    void nextStep();
    void finishCalculations();
    void endCalculations();
    void setBlocksForStepCalculations(QColor color);
    abstractBlock *getNextBlockForStepCalculations();
    void setPreviousLastCalculatedBlockColor();
    void setNextBlockForStepCalculations();
    bool checkEndOfStepCalculations();
    void setTool(int index);
    void createBlock(int index);
    void createToolbarForBlocks();
    void enableAfterForStepCalculations();
    void disableForStepCalculations();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
