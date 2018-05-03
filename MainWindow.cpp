#include "MainWindow.h"
#include "Block/BlocksFactory.h"
/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // nastaveni gui
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    registerTypes();

    // nastaveni velikosti a umisteni sceny
    this->scene->setSceneRect(0, 0, this->width() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, this->height() - this->MENU_HEIGHT - this->TOP_MARGIN);
    this->scene->setBackgroundBrush(QBrush(QColor(210,210,210), Qt::SolidPattern));
    this->ui->graphicsView->setScene(this->scene);

    setCentralWidget( this->ui->graphicsView );


    this->createToolbarForBlocks();
    this->createToolbarForStelCalculations();
    this->stepCalculations->hide();

    this->menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);
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
    blocksFactory(index, this->scene->width() / 2, this->scene->height() / 2, this->scene);
}

// po realesu mysi prida blok...
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (this->tool != this->TOOLS_NOT_ACTIVE && this->checkEndOfStepCalculations()) {
        blocksFactory(this->tool, event->localPos().x() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, event->localPos().y() - this->MENU_HEIGHT, this->scene);
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
AbstractBlock *MainWindow::getBlock(int index) {
    int count = 0;
    QGraphicsItemGroup *previous = nullptr;
    QGraphicsItemGroup *actual = nullptr;
    for (int i = 0; i < this->scene->items().length(); i++) {
        actual = this->scene->items().at(i)->group();
        if (actual != nullptr && actual != previous) {
            if (count == index) {
                return qgraphicsitem_cast<AbstractBlock *>(actual);
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
bool MainWindow::isInCycle(AbstractBlock *block) {
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
bool MainWindow::isBlockInBranch(AbstractBlock *block, AbstractBlock *branch) {
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
bool MainWindow::isEndBlock(AbstractBlock *block) {
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

bool MainWindow::readyForCalculation(AbstractBlock *block) {
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

void MainWindow::sendResultsByWire(AbstractBlock *block) {
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

void MainWindow::enableAfterStepCalculations() {
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

void MainWindow::createToolbarForStelCalculations() {
    this->stepCalculations = new QToolBar();

    QAction *nextStep = new QAction(tr("&Next step"), this);
    connect(nextStep, &QAction::triggered, this, &MainWindow::nextStep);
    nextStep->setIcon(QIcon(":/Resources/Resources/next.png"));
    this->stepCalculations->addAction(nextStep);

    QAction *finishCalculations = new QAction(tr("&Finish calculations"), this);
    connect(finishCalculations, &QAction::triggered, this, &MainWindow::finishCalculations);
    finishCalculations->setIcon(QIcon(":/Resources/Resources/finish.png"));
    this->stepCalculations->addAction(finishCalculations);

    QAction *endCalculations = new QAction(tr("&End calculations"), this);
    connect(endCalculations, &QAction::triggered, this, &MainWindow::endCalculations);
    endCalculations->setIcon(QIcon(":/Resources/Resources/stop.png"));
    this->stepCalculations->addAction(endCalculations);

    this->stepCalculations->setContextMenuPolicy(Qt::PreventContextMenu);
    this->stepCalculations->setIconSize(QSize(60,20));
    this->stepCalculations->adjustSize();
    this->stepCalculations->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addToolBar(this->stepCalculations);
}

void MainWindow::removeToolbarForStelCalculations(QToolBar *stepCalculations) { this->removeToolBar(stepCalculations); }

void MainWindow::nextStep() {
    AbstractBlock *nextBlock = this->getNextBlockForStepCalculations();
    nextBlock->doCalculation();
    this->sendResultsByWire(nextBlock);
    nextBlock->setCalculated(true);
    this->setPreviousLastCalculatedBlockColor();
    nextBlock->setBlockBorderColor(nextBlock->getLastCalculatedBorderColor());
    this->setNextBlockForStepCalculations();
    if (this->checkEndOfStepCalculations()) {
        this->setBlocksForStepCalculations(nextBlock->getDefaultBorderColor());
        this->stepCalculations->hide();
        this->enableAfterStepCalculations();
        QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
    }
}

void MainWindow::finishCalculations() {
    this->calculate();
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
    this->enableAfterStepCalculations();
    QMessageBox::information(this, "Calculations done", "Calculations successfully completed.");
}

void MainWindow::endCalculations() {
    this->setBlocksForStepCalculations(this->getBlock(0)->getDefaultBorderColor());
    this->stepCalculations->hide();
    this->enableAfterStepCalculations();
}

void MainWindow::setBlocksForStepCalculations(QColor color) {
    for (int i = 0; i < this->countBlocks(); i++) {
        this->getBlock(i)->setBlockBorderColor(color);
    }
}

AbstractBlock *MainWindow::getNextBlockForStepCalculations() {
    bool blockFound = false;
    AbstractBlock *block = nullptr;
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
            this->scene->update();
        }
    }
}

void MainWindow::setNextBlockForStepCalculations() {
    bool blockMarked = false;
    for (int i = 0; i < this ->countBlocks(); i ++) {
        if (this->getBlock(i)->getBlockBorderColor() == this->getBlock(i)->getNotCalculatedBorderColor()) {
            if (this->readyForCalculation(this->getBlock(i))) {
                this->getBlock(i)->setBlockBorderColor(this->getBlock(i)->getActualBorderColor());
                this->scene->update();
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

void MainWindow::on_action_Save_triggered() {
    QDomDocument scheme;

    QDomElement root = scheme.createElement("Scheme");
    scheme.appendChild(root);

    for(int i = 0; i < this->countBlocks(); i++){
        QDomElement block = scheme.createElement("Block");
        block.setAttribute("Type", this->getBlock(i)->getBlockType());
        block.setAttribute("X", this->getBlock(i)->startX+this->getBlock(i)->x() + this->getBlock(i)->getBlockWidth() / 2);
        block.setAttribute("Y", this->getBlock(i)->startY+this->getBlock(i)->y() + this->getBlock(i)->getBlockHeight() / 2);
        root.appendChild(block);
        for(int j = 0; j < this->getBlock(i)->getInPortsCount(); j++) {
            QDomElement portElement = scheme.createElement("Port");
            portElement.setAttribute("ID", this->getBlock(i)->getInPort(j)->getPortID());
            block.appendChild(portElement);
            for(int k = 0; k < this->getBlock(i)->getInPort(j)->getDataType()->getValuesLength(); k++){
                QDomElement valueElement = scheme.createElement("Value");
                valueElement.setAttribute("Value", this->getBlock(i)->getInPort(j)->getDataType()->getValue(k));
                if (this->getBlock(i)->getInPort(j)->getDataType()->getValuesSet()) {
                    valueElement.setAttribute("ValueSet", "1");
                } else {
                   valueElement.setAttribute("ValueSet", "0");
                }
                portElement.appendChild(valueElement);
            }
        }
        for(int j = 0; j < this->getBlock(i)->getOutPortsCount(); j++) {
            QDomElement portElement = scheme.createElement("Port");
            portElement.setAttribute("ID", this->getBlock(i)->getOutPort(j)->getPortID());
            block.appendChild(portElement);
            for(int k = 0; k < this->getBlock(i)->getOutPort(j)->getDataType()->getValuesLength(); k++){
                QDomElement valueElement = scheme.createElement("Value");
                valueElement.setAttribute("Value", this->getBlock(i)->getOutPort(j)->getDataType()->getValue(k));
                if (this->getBlock(i)->getOutPort(j)->getDataType()->getValuesSet()) {
                    valueElement.setAttribute("ValueSet", "1");
                } else {
                   valueElement.setAttribute("ValueSet", "0");
                }
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

    if (fileName.size() < 4) {
        fileName += ".sch";
    } else {
        if (fileName.at(fileName.size() - 4) != '.' || fileName.at(fileName.size() - 3) != 's' || fileName.at(fileName.size() - 2) != 'c' || fileName.at(fileName.size() - 1) != 'h') {
            fileName += ".sch";
        }
    }

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
        QDomNodeList ports = block.elementsByTagName("Port");

        blocksFactory(block.attribute("Type").toDouble(), block.attribute("X").toDouble(), block.attribute("Y").toDouble(), this->scene);

        for (int j = 0; j < this->getBlock(0)->getInPortsCount(); j++) {
            QDomElement port = ports.at(j).toElement();
            QDomNodeList values = port.elementsByTagName("Value");

            this->getBlock(0)->getInPort(j)->setPortID(port.attribute("ID").toInt());

            for (int k = 0; k < this->getBlock(0)->getInPort(j)->getDataType()->getValuesLength(); k++) {
                QDomElement value = values.at(k).toElement();
                this->getBlock(0)->getInPort(j)->getDataType()->setValue(k, value.attribute("Value").toDouble());
                if (value.attribute("ValueSet").toInt() == 1) {
                    this->getBlock(0)->getInPort(j)->getDataType()->setValuesSet(true);
                } else {
                    this->getBlock(0)->getInPort(j)->getDataType()->setValuesSet(false);
                }
            }
        }

        for (int j = 0; j < this->getBlock(0)->getOutPortsCount(); j++) {
            QDomElement port = ports.at(j + this->getBlock(0)->getInPortsCount()).toElement();
            QDomNodeList values = port.elementsByTagName("Value");

            this->getBlock(0)->getOutPort(j)->setPortID(port.attribute("ID").toInt());

            for (int k = 0; k < this->getBlock(0)->getOutPort(j)->getDataType()->getValuesLength(); k++) {
                QDomElement value = values.at(k).toElement();
                this->getBlock(0)->getOutPort(j)->getDataType()->setValue(k, value.attribute("Values").toDouble());
                if (value.attribute("ValueSet").toInt() == 1) {
                    this->getBlock(0)->getOutPort(j)->getDataType()->setValuesSet(true);
                } else {
                    this->getBlock(0)->getOutPort(j)->getDataType()->setValuesSet(false);
                }
            }
        }
    }
    QDomNodeList wires = xmlroot.elementsByTagName("Wire");
    for(int l = 0; l < wires.count(); l++) {
        Wire *tempWire = new Wire(this->scene);
        this->scene->addItem(tempWire);
        QDomElement wireElement = wires.at(l).toElement();
        for(int m = 0; m < this->countBlocks(); m++) {
            for(int n = 0; n < this->getBlock(m)->getOutPortsCount(); n++) {
                if(this->getBlock(m)->getOutPort(n)->getPortID() == wireElement.attribute("Out-Port").toInt()) {
                    this->getBlock(m)->getOutPort(n)->portWire = tempWire;
                    this->getBlock(m)->getOutPort(n)->getWire()->setEndPort(this->getBlock(m)->getOutPort(n));
                }
            }
            for(int o = 0; o < this->getBlock(m)->getInPortsCount(); o++) {
                if(this->getBlock(m)->getInPort(o)->getPortID() == wireElement.attribute("In-Port").toInt()) {
                    this->getBlock(m)->getInPort(o)->portWire = tempWire;
                    this->getBlock(m)->getInPort(o)->portWire = qgraphicsitem_cast<Wire *>(this->scene->items().first());
                    this->getBlock(m)->getInPort(o)->getWire()->setStartPort(this->getBlock(m)->getInPort(o));
                    this->getBlock(m)->getInPort(o)->getWire()->setDragFinished(true);
                    if (o == this->getBlock(m)->getInPortsCount() - 1) {
                        this->getBlock(m)->getInPort(o)->getNextId(true);
                    }
                }
            }
        }
    }
}
