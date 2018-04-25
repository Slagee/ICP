#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDialog>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include "Block/block1.h"
#include "Block/block2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionblock1_triggered();
    void on_actionblock2_triggered();

    void on_actionblock2_hovered();

    void on_actionblock1_hovered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Block1 *block1;
    Block2 *block2;
    QRectF *middle;
    int lastTool;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
