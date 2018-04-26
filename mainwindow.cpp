#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    toolBarWidth = 93;
    menuHeight = 55;
    scene->setSceneRect(0, 0, this->width() - toolBarWidth, this->height() - menuHeight);
    ui->graphicsView->setScene(scene);
    setCentralWidget( ui->graphicsView );   
    lastTool = 0;
}

MainWindow::~MainWindow() {
    delete ui;
}

// kliknuti na tool1 prida adder doprostred canvasu
void MainWindow::on_actionadder_triggered() {
    scene->addItem(new adder(this->width() / 2, this->height() / 2));
    qDebug("na scene je %d itemu", scene->items().length());
}

// kliknuti na tool2 prida subtractor doprostred canvasu
void MainWindow::on_actionsubtractor_triggered() {
    scene->addItem(new subtractor(this->width() / 2, this->height() / 2));
}

// po realesu mysi prida blok...
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    switch (lastTool) {
    case(1):
        scene->addItem(new adder(event->localPos().x() - 2 * toolBarWidth, event->localPos().y() - menuHeight));
        qDebug("na scene je %d itemu", scene->children().length());
        break;
    case(2):
        scene->addItem(new subtractor(event->localPos().x() - 2 * toolBarWidth, event->localPos().y() - menuHeight));
        break;
    }
}

// trosku hack - nastavi block, ktery se na pridat po drag and dropu...
void MainWindow::on_actionadder_hovered() { lastTool = 1; }
void MainWindow::on_actionsubtractor_hovered() { lastTool = 2; }
