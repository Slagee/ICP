#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, this->width() - 62, this->height() - 55);
    ui->graphicsView->setScene(scene);
    block2 = new Block2((qreal) 400,(qreal) 200);
    scene->addItem(block2);
    setCentralWidget( ui->graphicsView );   
    lastTool = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionblock1_triggered()
{
    block1 = new Block1();
    scene->addItem(block1);
}

void MainWindow::on_actionblock2_triggered()
{
    qDebug("There are %d blocks", scene->items().length());
    qDebug("scena ma %f x %f", scene->width(), scene->height());
    qDebug("Prvni blok je na pozici %f x %f", scene->items().last()->scenePos().x(), scene->items().last()->scenePos().y());
    qDebug("velikost okna je %d x %d", this->size().width(), this->height());
    block2 = new Block2((qreal) 10,(qreal) 10);
    scene->addItem(block2);
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("mys je na je na %f x %f", event->localPos().x(), event->localPos().y());
    qDebug("scena je na %f x %f", scene->sceneRect().x(), scene->sceneRect().y());
    block2 = new Block2(event->localPos().x() - 112, event->localPos().y() - 55);
    scene->addItem(block2);
}

void MainWindow::on_actionblock1_hovered() { lastTool = 1; }

void MainWindow::on_actionblock2_hovered() { lastTool = 2; }
