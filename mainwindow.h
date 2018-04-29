#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QtGui>

#include "ui_mainwindow.h"
#include "Block/abstractBlock.h"

namespace Ui { class MainWindow; }
class abstractBlock;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    qreal toolBarWidth;
    qreal menuHeight;
    int magicConstant1;
    int magicConstant2;

private slots:
    void on_actionadder_triggered();
    void on_actionadder_hovered();
    void on_actionsubtractor_hovered();
    void on_actionsubtractor_triggered();

    void on_actionNew_triggered();

    void on_actionCalculate_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    abstractBlock *block;
    QRectF *middle;
    int lastTool;

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
    void sendResultsByWire(abstractBlock *block) ;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
