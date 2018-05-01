#include "mainwindow.h"
#include "Block/adder.h"
#include "Block/subtractor.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    registrTypes();

    //this->

    // promenned pro vyreseni spravne pozice sceny
    this->toolBarWidth = 94;
    this->menuHeight = 25;
    this->magicConstant1 = 11;
    this->magicConstant2 = 30;

    // nastaveni velikosti a umisteni sceny
    this->scene->setSceneRect(0, 0, this->width() - this->toolBarWidth - this->magicConstant1, this->height() - this->menuHeight - this->magicConstant2);
    this->scene->setBackgroundBrush(QBrush(QColor(210,210,210), Qt::SolidPattern));
    this->ui->graphicsView->setScene(this->scene);
    setCentralWidget( this->ui->graphicsView );

    this->stepCalculations = this->createToolbarForStelCalculations();
    this->stepCalculations->hide();

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
    QMessageBox::StandardButton areYouSure;
    areYouSure = QMessageBox::question(this, "Are you sure?", "Do you really want to discard this block scheme?", QMessageBox::Yes|QMessageBox::No);
    if (areYouSure == QMessageBox::Yes) {
        while (this->scene->items().length() > 0) {
            delete this->scene->items().at(0);
        }
    }
}

// vypocet -> menu Run -> Calculate
void MainWindow::on_actionCalculate_triggered() {
    if (this->countBlocks() == 0) {
        QMessageBox::information(this, "Empty block scheme", "There is nothing to calculate...");
    } else if (this->findCycles()) {
        QMessageBox::warning(this, "Cycle detected!", "You have to remove all cycles!");
    } else {
        if (this->checkWirelessInPorts()) {
            this->setBlocksNotCalculated();
            this->calculate();
            QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
        } else {
            QMessageBox::warning(this, "Unfilled IN-ports detected!", "You have to fill values for all wireless IN-ports!");
        }
    }
}

void MainWindow::on_actionStep_Calculation_triggered() {
    if (this->countBlocks() == 0) {
        QMessageBox::information(this, "Empty block scheme", "There is nothing to calculate...");
    } else if (this->findCycles()) {
        QMessageBox::warning(this, "Cycle detected!", "You have to remove all cycles!");
    } else {
        if (this->checkWirelessInPorts()) {
            this->setBlocksForStepCalculations(this->getBlock(0)->getNotCalculatedBorderColor());
            this->setBlocksNotCalculated();
            this->setNextBlockForStepCalculations();
            if (!this->checkEndOfStepCalculations()) {
                this->stepCalculations->show();
            } else {
                QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
            }
        } else {
            QMessageBox::warning(this, "Unfilled IN-ports detected!", "You have to fill values for all wireless IN-ports!");
        }
    }
}

QToolBar *MainWindow::createToolbarForStelCalculations() {
    QToolBar *stepCalculations = new QToolBar();

    QAction *nextStep = new QAction(tr("&Next step"), this);
    connect(nextStep, &QAction::triggered, this, &MainWindow::nextStep);
    stepCalculations->addAction(nextStep);

    QAction *finishCalculations = new QAction(tr("&Finish calculations"), this);
    connect(finishCalculations, &QAction::triggered, this, &MainWindow::finishCalculations);
    stepCalculations->addAction(finishCalculations);

    QAction *endCalculations = new QAction(tr("&Finish calculations"), this);
    connect(endCalculations, &QAction::triggered, this, &MainWindow::endCalculations);
    stepCalculations->addAction(endCalculations);

    this->addToolBar(stepCalculations);
    return stepCalculations;
}

void MainWindow::removeToolbarForStelCalculations(QToolBar *stepCalculations) { this->removeToolBar(stepCalculations); }

void MainWindow::nextStep() {
    abstractBlock *nextBlock = this->getNextBlockForStepCalculations();
    nextBlock->doCalculation();
    this->sendResultsByWire(nextBlock);
    nextBlock->setCalculated(true);
    this->setPreviousLastCalculatedBlockColor();
    nextBlock->setBlockBorderColor(nextBlock->getLastCalculatedBorderColor());
    this->setNextBlockForStepCalculations();
    if (this->checkEndOfStepCalculations()) {
        this->setBlocksForStepCalculations(nextBlock->getDefaultBorderColor());
        this->stepCalculations->hide();
        QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
    }
}

void MainWindow::finishCalculations() {
    this->calculate();
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
    QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
}

void MainWindow::endCalculations() {
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
}

void MainWindow::setBlocksForStepCalculations(QColor color) {
    for (int i = 0; i < this->countBlocks(); i++) {
        this->getBlock(i)->setBlockBorderColor(color);
    }
}

abstractBlock *MainWindow::getNextBlockForStepCalculations() {
    bool blockFound = false;
    abstractBlock *block = nullptr;
    int k = 0;
    while (k < this->countBlocks() && !blockFound) {
        if (this->getBlock(k)->getBlockBorderColor() == this->getBlock(k)->getActualBorderColor()) {
            block = this->getBlock(k);
            blockFound = true;
        }
        k++;
    }
    return block;
}

void MainWindow::setPreviousLastCalculatedBlockColor() {
    for (int i = 0; i < this->countBlocks(); i++) {
        if (this->getBlock(i)->getBlockBorderColor() == this->getBlock(i)->getLastCalculatedBorderColor()) {
            this->getBlock(i)->setBlockBorderColor(this->getBlock(i)->getCalculated());
        }
    }
}

void MainWindow::setNextBlockForStepCalculations() {
    bool blockMarked = false;
    for (int i = 0; i < this ->countBlocks(); i ++) {
        if (this->getBlock(i)->getBlockBorderColor() == this->getBlock(i)->getNotCalculatedBorderColor()) {
            if (this->readyForCalculation(this->getBlock(i))) {
                this->getBlock(i)->setBlockBorderColor(this->getBlock(i)->getActualBorderColor());
                blockMarked = true;
            }
        }
        if (blockMarked) { i = this->countBlocks(); }
    }
}

bool MainWindow::checkEndOfStepCalculations() {
    for (int i = 0; i < this->countBlocks(); i++) {
        if (this->getBlock(i)->getBlockBorderColor() == this->getBlock(i)->getActualBorderColor()) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionnapoveda_triggered() {
    QMessageBox::information(this, "Help", "The application is used for creating/editing block schemas.\n\nYou can add new block by dragging from toolbar.\n\nYou can fill in-port values by rightclick on single port\nor you can fill all blocks in-ports by righclick on whole block.\n\nYou can delete block by rightclick on block.\n\nYou can calculate your scheme through run menu.\n\nYou can save or import your schema through file menu.\n\nPort colors indicates port status and functionality:\nred is for wireless in-port with not filled values\nblue is for wireless out-port\nblack is for wired in-port/out-port\ngreen is for wireless in-port witch filled values\nyellow is for focused in-port/out-port");
}
