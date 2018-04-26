#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QDialog>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include "Block/abstractblock.h"
#include "Block/adder.h"
#include "Block/subtractor.h"
#include "Port/port.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionadder_triggered();
    void on_actionadder_hovered();
    void on_actionsubtractor_hovered();
    void on_actionsubtractor_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    abstractblock *block;
    QRectF *middle;
    int lastTool;
    qreal toolBarWidth;
    qreal menuHeight;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
