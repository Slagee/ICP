/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "MainWindow.h"
#include "Block/BlocksFactory.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // nastaveni gui
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);

    registerTypes();

    // nastaveni velikosti a umisteni sceny
    this->scene->setSceneRect(0, 0, this->width() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, this->height() - this->MENU_HEIGHT - this->TOP_MARGIN);
    this->scene->setBackgroundBrush(QBrush(QColor(210,210,210), Qt::SolidPattern));
    this->ui->graphicsView->setScene(this->scene);
    this->setCentralWidget( this->ui->graphicsView );

    this->createToolbarForBlocks();
    this->createToolbarForStelCalculations();
    this->stepCalculations->hide();

    this->menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);
}

MainWindow::~MainWindow() {
    delete this->ui;
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

void MainWindow::createToolbarForBlocks() {
    this->toolsForBlocks = new QToolBar();

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
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

void MainWindow::setTool(int index) { this->tool = index; }

void MainWindow::createBlock(int index) { blocksFactory(index, this->scene->width() / 2, this->scene->height() / 2, this->scene); }

int MainWindow::getToolbarWidth() { return this->TOOLBAR_WIDTH; }

int MainWindow::getMenuHeight() { return this->MENU_HEIGHT; }

int MainWindow::getToolbarMargin() { return this->TOOLBAR_MARGIN; }

// po realesu mysi prida blok...
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (this->tool != this->TOOLS_NOT_ACTIVE && this->checkEndOfStepCalculations()) {
        if (!(((event->localPos().x() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN) < 0) || ((event->localPos().y() - this->MENU_HEIGHT) < 0) || ((event->localPos().x() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN) > this->scene->width()) || ((event->localPos().y() - this->MENU_HEIGHT) > this->scene->height()))) {
            blocksFactory(this->tool, event->localPos().x() - this->TOOLBAR_WIDTH - 2 * this->TOOLBAR_MARGIN, event->localPos().y() - this->MENU_HEIGHT, this->scene);
        }
        this->tool = this->TOOLS_NOT_ACTIVE;
    }

    Q_UNUSED(event);
}

// vycisteni canvasu --> menu File --> New
void MainWindow::on_actionNew_triggered() {
    QMessageBox::StandardButton areYouSure;
    areYouSure = QMessageBox::question(this, "Are you sure?", "Do you really want to discard this block scheme?", QMessageBox::Yes|QMessageBox::No);
    if (areYouSure == QMessageBox::Yes) {
        while (this->scene->items().length() > 0) {
            delete this->scene->items().at(0);
        }
    }
}

// vypocet --> menu Run --> Calculate
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

// krokvani --> menu Run --> Step calculations
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

// napoveda --> menu Help
void MainWindow::on_actionHelp_triggered() { QMessageBox::information(this, "Help", "The application is used for creating/editing block schemas.\n\nYou can add new block by dragging from toolbar or by leftclick on toolbar you can add block to the middle of canvas.\n\nYou can fill in-port values by rightclick on single port\nor you can fill all blocks in-ports by righclick on whole block.\n\nYou can delete block by doubleclick on block.\n\nYou can calculate your scheme through run menu.\n\nYou can save or import your schema through file menu.\n\nPort colors indicates port status and functionality:\nred is for wireless in-port with not filled values\nblue is for wireless out-port\nblack is for wired in-port/out-port\ngreen is for wireless in-port witch filled values\nyellow is for focused in-port/out-port"); }

// ulozeni --> menu File --> Save
void MainWindow::on_action_Save_triggered() {
    QDomDocument scheme;
    QDomElement root = scheme.createElement("Scheme");
    scheme.appendChild(root);

    QDomElement block;
    QDomElement portElement;
    QDomElement valueElement;
    QDomElement wireElement;

    AbstractBlock *blockToProcess = nullptr;
    Port *portToProcess = nullptr;

    // vytvoreni xml struktury pro canvas
    for(int i = 0; i < this->countBlocks(); i++){

        // ulozeni informaci o bloku
        block = scheme.createElement("Block");
        blockToProcess = this->getBlock(i);
        block.setAttribute("Type", getClassIdFromClassName(blockToProcess->getBlockClassName()));
        block.setAttribute("X", blockToProcess->startX + blockToProcess->x() + blockToProcess->getBlockWidth() / 2);
        block.setAttribute("Y", blockToProcess->startY + blockToProcess->y() + blockToProcess->getBlockHeight() / 2);
        root.appendChild(block);

        // o in-portech bloku
        for(int j = 0; j < blockToProcess->getInPortsCount(); j++) {
            portElement = scheme.createElement("Port");
            portToProcess = blockToProcess->getInPort(j);
            portElement.setAttribute("ID", portToProcess->getPortID());
            block.appendChild(portElement);

            // o vsech hodnotach portu
            for(int k = 0; k < portToProcess->getDataType()->getValuesLength(); k++){
                valueElement = scheme.createElement("Value");
                valueElement.setAttribute("Value", portToProcess->getDataType()->getValue(k));
                if (portToProcess->getDataType()->getValuesSet()) {
                    valueElement.setAttribute("ValueSet", "1");
                } else {
                   valueElement.setAttribute("ValueSet", "0");
                }
                portElement.appendChild(valueElement);
            }
        }

        // o out-portech bloku
        for(int j = 0; j < blockToProcess->getOutPortsCount(); j++) {
            portElement = scheme.createElement("Port");
            portToProcess = blockToProcess->getOutPort(j);
            portElement.setAttribute("ID", portToProcess->getPortID());
            block.appendChild(portElement);

            // o vsech hondotach portu
            for(int k = 0; k < portToProcess->getDataType()->getValuesLength(); k++){
                valueElement = scheme.createElement("Value");
                valueElement.setAttribute("Value", portToProcess->getDataType()->getValue(k));
                if (portToProcess->getDataType()->getValuesSet()) {
                    valueElement.setAttribute("ValueSet", "1");
                } else {
                    valueElement.setAttribute("ValueSet", "0");
                }
                portElement.appendChild(valueElement);
            }
        }

        // o dratech
        for(int j = 0; j < blockToProcess->getOutPortsCount(); j++) {
            if(blockToProcess->getOutPort(j)->getWire() != nullptr) {
                wireElement = scheme.createElement("Wire");
                portToProcess = blockToProcess->getOutPort(j);
                wireElement.setAttribute("Out-Port", portToProcess->getPortID());
                wireElement.setAttribute("In-Port", portToProcess->getWire()->getOtherPort(portToProcess)->getPortID());
                root.appendChild(wireElement);
            }
        }
    }

    // zjisteni kam to ulozit
    QString fileName = QFileDialog::getSaveFileName(this,"Save Scheme", "", "Scheme (*.sch)", 0, QFileDialog::DontUseNativeDialog);

    // pridani suffixu
    if (fileName.size() < 4) {
        fileName += ".sch";
    } else {
        if (fileName.at(fileName.size() - 4) != '.' || fileName.at(fileName.size() - 3) != 's' || fileName.at(fileName.size() - 2) != 'c' || fileName.at(fileName.size() - 1) != 'h') {
            fileName += ".sch";
        }
    }

    // ulozeni
    if (fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file."), file.errorString());
            return;
        }
        QTextStream stream(&file);
        stream << scheme.toString();
        file.close();
    }
}

// otevreni --> menu File --> Open
void MainWindow::on_action_Open_triggered() {
    QDomDocument scheme;

    // co otevrit
    QString fileName = QFileDialog::getOpenFileName(this, "Open Scheme", "", "Scheme (*.sch)", 0, QFileDialog::DontUseNativeDialog);

    // nacteni souboru
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

    // vycisteni canvasu
    while (this->scene->items().length() > 0) { delete this->scene->items().at(0); }

    QDomElement xmlroot = scheme.firstChildElement();
    QDomNodeList blocks = xmlroot.elementsByTagName("Block");
    QDomElement block;
    QDomNodeList ports;
    QDomElement port;
    QDomNodeList values;
    QDomElement value;

    AbstractBlock *blockToProcess = nullptr;
    Port *portToProcess = nullptr;

    // nacteni bloku
    for(int i = 0; i < blocks.count(); i++) {
        block = blocks.at(i).toElement();
        ports = block.elementsByTagName("Port");
        blocksFactory(block.attribute("Type").toDouble(), block.attribute("X").toDouble(), block.attribute("Y").toDouble(), this->scene);
        blockToProcess = this->getBlock(0);

        // nacteni hodnot na vstupnich portech
        for (int j = 0; j < blockToProcess->getInPortsCount(); j++) {
            port = ports.at(j).toElement();
            values = port.elementsByTagName("Value");
            portToProcess = blockToProcess->getInPort(j);
            portToProcess->setPortID(port.attribute("ID").toInt());

            // vsechny hodnoty portu...
            for (int k = 0; k < portToProcess->getDataType()->getValuesLength(); k++) {
                value = values.at(k).toElement();
                portToProcess->getDataType()->setValue(k, value.attribute("Value").toDouble());
                if (value.attribute("ValueSet").toInt() == 1) {
                    portToProcess->getDataType()->setValuesSet(true);
                } else {
                    portToProcess->getDataType()->setValuesSet(false);
                }
            }
        }

        // nacteni hodnot na vstupnich portech
        for (int j = 0; j < blockToProcess->getOutPortsCount(); j++) {
            port = ports.at(j + blockToProcess->getInPortsCount()).toElement();
            values = port.elementsByTagName("Value");
            portToProcess = blockToProcess->getOutPort(j);
            portToProcess->setPortID(port.attribute("ID").toInt());

            // vsechny hodnoty portu...
            for (int k = 0; k < portToProcess->getDataType()->getValuesLength(); k++) {
                value = values.at(k).toElement();
                portToProcess->getDataType()->setValue(k, value.attribute("Values").toDouble());
                if (value.attribute("ValueSet").toInt() == 1) {
                    portToProcess->getDataType()->setValuesSet(true);
                } else {
                    portToProcess->getDataType()->setValuesSet(false);
                }
            }
        }
    }

    // nastaveni citace idcek
    if (blocks.count() > 0) { this->getBlock(0)->getInPort(0)->getNextId(true); }

    QDomNodeList wires = xmlroot.elementsByTagName("Wire");
    QDomElement wireElement;
    Wire *tempWire = nullptr;
    int portId = 0;

    // nacteni dratu, pro kazdy drat
    for(int i = 0; i < wires.count(); i++) {
        tempWire = new Wire(this->scene);
        this->scene->addItem(tempWire);
        wireElement = wires.at(i).toElement();

        // pres vsechny bloku
        for(int j = 0; j < this->countBlocks(); j++) {

            blockToProcess = this->getBlock(j);
            portId = wireElement.attribute("Out-Port").toInt();

            // najdu jeho vystupni
            for(int k = 0; k < blockToProcess->getOutPortsCount(); k++) {
                portToProcess = blockToProcess->getOutPort(k);
                if(portToProcess->getPortID() == portId) {
                    portToProcess->setWire(tempWire);
                    portToProcess->getWire()->setEndPort(portToProcess);
                }
            }

            portId = wireElement.attribute("In-Port").toInt();

            // a vstupni port
            for(int k = 0; k < blockToProcess->getInPortsCount(); k++) {
                portToProcess = blockToProcess->getInPort(k);
                if(portToProcess->getPortID() == portId) {
                    portToProcess->setWire(tempWire);
                    portToProcess->getWire()->setStartPort(portToProcess);
                    portToProcess->getWire()->setDragFinished(true);
                }
            }
        }
    }
}

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

bool MainWindow::findCycles() {
    for (int i = 0; i < this->countBlocks(); i++) {
        if (this->isInCycle(this->getBlock(i))) { return true; }
    }
    return false;
}

void MainWindow::setPortsForFindingCycles() {
    for (int i = 0; i < this->countBlocks(); i++) {
        for (int j = 0; j < this->getBlock(i)->getOutPortsCount(); j++) {
            this->getBlock(i)->getOutPort(j)->setIsInCycle(false);
        }
    }
}

bool MainWindow::isInCycle(AbstractBlock *block) {
    for (int i = 0; i < block->getOutPortsCount(); i++) {
        if (block->getOutPort(i)->getWire() != nullptr) {
            this->setPortsForFindingCycles();
            if (isBlockInBranch(block, block->getOutPort(i)->getWire()->getOtherPort(block->getOutPort(i))->myParent)) {
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::isBlockInBranch(AbstractBlock *block, AbstractBlock *branch) {
    if (branch->getOutPort(0)->getIsInCycle()) { return true; }
    if (block == branch) {
        return true;
    } else {
        if (this->isEndBlock(branch)) {
            return false;
        } else {
            for (int i = 0; i < branch->getOutPortsCount(); i++) {
                branch->getOutPort(i)->setIsInCycle(true);
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
    AbstractBlock *block = nullptr;
    while (!allDone) {
        allDone = true;
        for (int i = 0; i < this->countBlocks(); i++) {
            block = this->getBlock(i);
            if (!block->getCalculated()) {
                if (this->readyForCalculation(block)) {
                    block->doCalculation();
                    this->sendResultsByWire(block);
                    block->setCalculated(true);
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
    AbstractBlock *block = nullptr;
    for (int i = 0; i < this->countBlocks(); i++) {
        block = this->getBlock(i);
        for (int j = 0; j < block->getInPortsCount(); j++) {
            if (block->getInPort(j)->getWire() == nullptr) {
                if (!block->getInPort(j)->getDataType()->getValuesSet()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MainWindow::sendResultsByWire(AbstractBlock *block) {
    Port *port = nullptr;
    for (int i = 0; i < block->getOutPortsCount(); i++) {
        port = block->getOutPort(i);
        if (port->getWire() != nullptr) {
            for (int j = 0; j < port->getDataType()->getValuesLength(); j++) {
                port->getWire()->getOtherPort(port)->getDataType()->setValue(j, port->getDataType()->getValue(j));
            }
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
    AbstractBlock *abstractBlock = nullptr;
    int i = 0;
    while (i < this->countBlocks() && !blockFound) {
        abstractBlock = this->getBlock(i);
        if (abstractBlock->getBlockBorderColor() == abstractBlock->getActualBorderColor()) {
            block = abstractBlock;
            blockFound = true;
        }
        i++;
    }
    return block;
}

void MainWindow::setPreviousLastCalculatedBlockColor() {
    AbstractBlock *block = nullptr;
    for (int i = 0; i < this->countBlocks(); i++) {
        block = this->getBlock(i);
        if (block->getBlockBorderColor() == block->getLastCalculatedBorderColor()) {
            block->setBlockBorderColor(block->getCalculatedBorderColor());
            this->scene->update();
        }
    }
}

void MainWindow::setNextBlockForStepCalculations() {
    bool blockMarked = false;
    AbstractBlock *block = nullptr;
    for (int i = 0; i < this ->countBlocks(); i ++) {
        block = this->getBlock(i);
        if (block->getBlockBorderColor() == block->getNotCalculatedBorderColor()) {
            if (this->readyForCalculation(block)) {
                block->setBlockBorderColor(block->getActualBorderColor());
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
