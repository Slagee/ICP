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
    qDebug() << "itemu tu je " << scene->items().length();
    qDebug() << "deti mam " << scene->children().size();

    for (int i = 0; i < scene->items().length(); i++) {
        qDebug() << i << " je " << scene->items().at(i)->group();
    }
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

// spocita bloky a vrati jejich pocet
int MainWindow::countBlocks() {
   int count = 0;
   QGraphicsItemGroup *previous = nullptr;
   QGraphicsItemGroup *actual = nullptr;
   for (int i = 0; i < this->scene->items().length(); i++) {
       actual = this->scene->items().at(i)->group();
       if (actual != nullptr && actual != previous) { count++; }
       previous = actual;
   }
   return count;
}

// vrati blok s danym indexem
abstractBlock *MainWindow::getBlock(int index) {
    int count = 0;
    QGraphicsItemGroup *previous = nullptr;
    QGraphicsItemGroup *actual = nullptr;
    for (int i = 0; i < this->scene->items().length(); i++) {
        actual = this->scene->items().at(i)->group();
        if (actual != nullptr && actual != previous) {
            if (count == index) {
                return qgraphicsitem_cast<abstractBlock *>(actual);
            }
            count++;
        }
        previous = actual;
    }
    return nullptr;
}

// zkontroluje, zdali nejsou ve schematu cykly - vraci true/false...
bool MainWindow::findCycles() {
    for (int i = 0; i < this->countBlocks(); i++) {
        if (this->isInCycle(this->getBlock(i))) { return true; }
    }
    return false;
}

// zkontroluje, zdali blok neni v cyklu - vraci true/false...
bool MainWindow::isInCycle(abstractBlock *block) {
    for (int i = 0; i < block->getOutPortsCount(); i++) {
        if (block->getOutPort(i)->getWire() != nullptr) {
            if (isBlockInBranch(block, block->getOutPort(i)->getWire()->getOtherPort(block->getOutPort(i))->myParent)) {
                return true;
            }
        }
    }
    return false;
}

// zjisti zdaje je block ve vetvi..
bool MainWindow::isBlockInBranch(abstractBlock *block, abstractBlock *branch) {
    if (block == branch) {
        return true;
    } else {
        if (this->isEndBlock(branch)) {
            return false;
        } else {
            for (int i = 0; i < branch->getOutPortsCount(); i++) {
                if (branch->getOutPort(i)->getWire() != nullptr) {
                    if (isBlockInBranch(block, branch->getOutPort(i)->getWire()->getOtherPort(branch->getOutPort(i))->myParent)) {
                        return true;
                    }
                }
            }
            return false;
        }
    }
}

// zjisti zdali se jedan o koncovy blok
bool MainWindow::isEndBlock(abstractBlock *block) {
    for (int i = 0; i < block->getOutPortsCount(); i++) {
        if (block->getOutPort(i)->getWire() != nullptr) {
            return false;
        }
    }
    return true;
}

void MainWindow::calculate() {
    bool allDone = false;
    while (!allDone) {
        allDone = true;
        for (int i = 0; i < this->countBlocks(); i++) {
            if (!this->getBlock(i)->getCalculated()) {
                if (this->readyForCalculation(this->getBlock(i))) {
                    this->getBlock(i)->doCalculation();
                    this->sendResultsByWire(this->getBlock(i));
                    this->getBlock(i)->setCalculated(true);
                } else {
                    allDone = false;
                }
            }
        }
    }
}

bool MainWindow::readyForCalculation(abstractBlock *block) {
    for (int i = 0; i < block->getInPortsCount(); i++) {
        if (block->getInPort(i)->getWire() != nullptr) {
            if (!block->getInPort(i)->getWire()->getOtherPort(block->getInPort(i))->myParent->getCalculated()) {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::setBlocksNotCalculated() {
    for (int i = 0; i < this->countBlocks(); i++) {
        this->getBlock(i)->setCalculated(false);
    }
}

bool MainWindow::checkWirelessInPorts() {
    for (int i = 0; i < this->countBlocks(); i++) {
        for (int j = 0; j < this->getBlock(i)->getInPortsCount(); j++) {
            if (this->getBlock(i)->getInPort(j)->getWire() == nullptr) {
                if (!this->getBlock(i)->getInPort(j)->getDataType()->getValuesSet()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MainWindow::sendResultsByWire(abstractBlock *block) {
    for (int i = 0; i < block->getOutPortsCount(); i++) {
        if (block->getOutPort(i)->getWire() != nullptr) {
            for (int j = 0; j < block->getOutPort(i)->getDataType()->getValuesLength(); j++) {
                block->getOutPort(i)->getWire()->getOtherPort(block->getOutPort(i))->getDataType()->setValue(j, block->getOutPort(i)->getDataType()->getValue(j));
            }
        }
    }
}

// vycisteni canvasu --> menu File -> New
void MainWindow::on_actionNew_triggered() {
    while (this->scene->items().length() > 0) {
        delete this->scene->items().at(0);
    }
}

// vypocet -> menu Run -> Calculate
void MainWindow::on_actionCalculate_triggered() {
    if (this->findCycles()) {
        qDebug("Je tu cyklus!");
    } else {
        if (this->checkWirelessInPorts()) {
            this->setBlocksNotCalculated();
            this->calculate();
            qDebug("Vypocet hotovy!");
        } else {
            qDebug("Musis vyplnit vsechny in-porty bez dratu...");
        }
    }
}
