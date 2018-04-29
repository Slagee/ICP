#include "mainwindow.h"
#include "Block/adder.h"
#include "Block/subtractor.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    // promenned pro vyreseni spravne pozice sceny
    this->toolBarWidth = 93;
    this->menuHeight = 25;
    this->magicConstant1 = 11;
    this->magicConstant2 = 29;

    // nastaveni velikosti a umisteni sceny
    this->scene->setSceneRect(0, 0, this->width() - this->toolBarWidth - this->magicConstant1, this->height() - this->menuHeight - this->magicConstant2);

    this->ui->graphicsView->setScene(this->scene);
    setCentralWidget( this->ui->graphicsView );

    this->lastTool = 0;
}

MainWindow::~MainWindow() {
    delete this->ui;
}

// kliknuti na tool1 prida adder doprostred canvasu
void MainWindow::on_actionadder_triggered() {
    this->scene->addItem(new adder(this->width() / 2, this->height() / 2, this->scene));
}

// kliknuti na tool2 prida subtractor doprostred canvasu
void MainWindow::on_actionsubtractor_triggered() {
    this->scene->addItem(new subtractor(this->width() / 2, this->height() / 2, this->scene));
}

// po realesu mysi prida blok...
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    switch (this->lastTool) {
    case(1):
        this->scene->addItem(new adder(event->localPos().x() - this->toolBarWidth, event->localPos().y() - this->menuHeight, this->scene));
        break;
    case(2):
        this->scene->addItem(new subtractor(event->localPos().x() - this->toolBarWidth, event->localPos().y() - this->menuHeight, this->scene));
        break;
    }
}

// trosku hack - nastavi block, ktery se na pridat po drag and dropu...
void MainWindow::on_actionadder_hovered() { this->lastTool = 1; }

void MainWindow::on_actionsubtractor_hovered() { this->lastTool = 2; }
