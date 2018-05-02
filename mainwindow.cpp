#include "mainwindow.h"
#include "Block/blocksfactory.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    registrTypes();
    createToolbarForBlocks();

    // nastaveni velikosti a umisteni sceny
    this->scene->setSceneRect(0, 0, this->width() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, this->height() - this->MENU_HEIGHT - this->TOP_MARGIN);
    this->scene->setBackgroundBrush(QBrush(QColor(210,210,210), Qt::SolidPattern));
    this->ui->graphicsView->setScene(this->scene);

    setCentralWidget( this->ui->graphicsView );

    this->stepCalculations = this->createToolbarForStelCalculations();
    this->stepCalculations->hide();

    this->menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);

    //qDebug() << " toolbarspacing " << this->toolsForBlocks->styleSheet();

    /*
    qDebug() << "veci tu je " << this->scene->items().length();
    for (int i = 0; i < this->scene->items().length(); i++) {
        qDebug() << i+1 << " je " << this->scene->items().at(i);
    }
    */


}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::createToolbarForBlocks() {
    this->toolsForBlocks = new QToolBar();

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        //QAction *toolBlock = new QAction(tr(BLOCKS_CLASSES[i].toUtf8().constData()), this);
        QAction *toolBlock = new QAction(this);
        toolBlock->setIcon(QIcon(":/Resources/Resources/" + BLOCKS_CLASSES[i] + ".png"));
        connect(toolBlock, &QAction::hovered, this, [this, i]{ setTool(i); });
        connect(toolBlock, &QAction::triggered, this, [this, i]{ createBlock(i); });
        this->toolsForBlocks->addAction(toolBlock);
    }

    this->addToolBar(Qt::LeftToolBarArea, toolsForBlocks);
    this->toolsForBlocks->setOrientation(Qt::Vertical);
    this->toolsForBlocks->setMovable(false);
    this->toolsForBlocks->setIconSize(QSize(this->TOOLBAR_WIDTH,this->TOOLBAR_HEIGHT));
    this->toolsForBlocks->setContextMenuPolicy(Qt::PreventContextMenu);
}
/*
std::string MainWindo::getTooltipForTool(int i) {
   std::string tooltip = "";

}
*/
int MainWindow::getToolbarWidth() { return this->TOOLBAR_WIDTH; }

int MainWindow::getMenuHeight() { return this->MENU_HEIGHT; }

int MainWindow::getToolbarMargin() { return this->TOOLBAR_MARGIN; }

void MainWindow::setTool(int index) {
    //this->toolsActive = true;
    this->tool = index;
}

void MainWindow::createBlock(int index) {
    blocksfactory(index, this->scene->width() / 2, this->scene->height() / 2, this->scene);
}

// po realesu mysi prida blok...
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (this->tool != this->TOOLS_NOT_ACTIVE) {
        blocksfactory(this->tool, event->localPos().x() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, event->localPos().y() - this->MENU_HEIGHT, this->scene);
        this->tool = this->TOOLS_NOT_ACTIVE;
    }
}

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
                this->disableForStepCalculations();
            } else {
                QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
            }
        } else {
            QMessageBox::warning(this, "Unfilled IN-ports detected!", "You have to fill values for all wireless IN-ports!");
        }
    }
}

void MainWindow::disableForStepCalculations() {
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        this->toolsForBlocks->actions().at(i)->setDisabled(true);
        this->menuBar()->actions().at(0)->setDisabled(true);
        this->menuBar()->actions().at(1)->setDisabled(true);
    }
}

void MainWindow::enableAfterForStepCalculations() {
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        this->toolsForBlocks->actions().at(i)->setEnabled(true);
        this->menuBar()->actions().at(0)->setEnabled(true);
        this->menuBar()->actions().at(1)->setEnabled(true);
    }
}

bool MainWindow::getWireEnabled() {
    if (this->toolsForBlocks->actions().at(0)->isEnabled()) {
        return true;
    }
    return false;
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

    stepCalculations->setContextMenuPolicy(Qt::PreventContextMenu);
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
        this->enableAfterForStepCalculations();
        QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
    }
}

void MainWindow::finishCalculations() {
    this->calculate();
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
    this->enableAfterForStepCalculations();
    QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
}

void MainWindow::endCalculations() {
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
    this->enableAfterForStepCalculations();
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

void MainWindow::on_actionHelp_triggered() {
    QMessageBox::information(this, "Help", "The application is used for creating/editing block schemas.\n\nYou can add new block by dragging from toolbar.\n\nYou can fill in-port values by rightclick on single port\nor you can fill all blocks in-ports by righclick on whole block.\n\nYou can delete block by rightclick on block.\n\nYou can calculate your scheme through run menu.\n\nYou can save or import your schema through file menu.\n\nPort colors indicates port status and functionality:\nred is for wireless in-port with not filled values\nblue is for wireless out-port\nblack is for wired in-port/out-port\ngreen is for wireless in-port witch filled values\nyellow is for focused in-port/out-port");
}
/*
void MainWindow::on_actionnapoveda_triggered() {
    qDebug("boom");
}
*/

void MainWindow::on_action_Save_triggered() {
    QDomDocument scheme;

    QDomElement root = scheme.createElement("Scheme");
    scheme.appendChild(root);

    for(int i = 0; i < this->countBlocks(); i++){
        QDomElement block = scheme.createElement("Block");
        block.setAttribute("Type", this->getBlock(i)->getBlockType());
        block.setAttribute("X", this->getBlock(i)->startX+this->getBlock(i)->x());
        block.setAttribute("Y", this->getBlock(i)->startY+this->getBlock(i)->y());
        root.appendChild(block);
        for(int j = 0; j < this->getBlock(i)->getInPortsCount(); j++) {
            QDomElement portElement = scheme.createElement("Port");
            portElement.setAttribute("ID", this->getBlock(i)->getInPort(j)->getPortID());
            block.appendChild(portElement);
            for(int k = 0; k < this->getBlock(i)->getInPort(j)->getDataType()->getValuesLength(); k++){
                QDomElement valueElement = scheme.createElement("Value");
                valueElement.setAttribute("Value", this->getBlock(i)->getInPort(j)->getDataType()->getValue(k));
                portElement.appendChild(valueElement);
            }
        }
        for(int k = 0; k < this->getBlock(i)->getOutPortsCount(); k++) {
            if(this->getBlock(i)->getOutPort(k)->getWire() != nullptr) {
                QDomElement wireElement = scheme.createElement("Wire");
                wireElement.setAttribute("Out-Port", this->getBlock(i)->getOutPort(k)->getPortID());
                wireElement.setAttribute("In-Port", this->getBlock(i)->getOutPort(k)->getWire()->getOtherPort(this->getBlock(i)->getOutPort(k))->getPortID());
                root.appendChild(wireElement);
            }
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this,"Save Scheme", "", "Scheme (*.sch)", 0, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        QTextStream stream(&file);
        stream << scheme.toString();
        file.close();
    }
}

void MainWindow::on_action_Open_triggered() {
    QDomDocument scheme;

    QString fileName = QFileDialog::getOpenFileName(this, "Open Scheme", "", "Scheme (*.sch)", 0, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Unable to open file", file.errorString());
            return;
        }
        scheme.setContent(&file);
        file.close();
    }
    while (this->scene->items().length() > 0) {
        delete this->scene->items().at(0);
    }

    QDomElement xmlroot = scheme.firstChildElement();

    QDomNodeList blocks = xmlroot.elementsByTagName("Block");
    for(int i = 0; i < blocks.count(); i++) {
        QDomElement block = blocks.at(i).toElement();
        blocksfactory(block.attribute("Type").toDouble(), block.attribute("X").toDouble() + this->TOOLBAR_WIDTH + 2 * this->TOOLBAR_MARGIN, block.attribute("Y").toDouble() + this->MENU_HEIGHT, this->scene);
        settingPortID();
        QDomNodeList ports = block.elementsByTagName("Port");
        for(int j = 0; j < ports.count(); j++) {
            QDomElement port = ports.at(j).toElement();
            if(port.attribute("ID").toDouble() == this->getBlock(0)->getInPort(j)->getPortID()) {
                for(int k = 0; k < this->getBlock(0)->getInPort(j)->getDataType()->getValuesLength(); k++)
                    this->getBlock(0)->getInPort(j)->getDataType()->setValue(k, port.attribute("Value").toDouble());
            }
        }
    }
}

void MainWindow::settingPortID() {
    static int IDCounter = 0;
    this->newID = IDCounter;
    for(int j = 0; j < this->getBlock(0)->getInPortsCount(); j++){
        this->getBlock(0)->getInPort(j)->setPortID(IDCounter);
        IDCounter++;
    }
    for(int i = 0; i < this->getBlock(0)->getOutPortsCount(); i++) {
        this->getBlock(0)->getOutPort(i)->setPortID(IDCounter);
        IDCounter++;
    }
}
