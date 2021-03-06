/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Port.h"

Port::Port(QString dataTypeName, AbstractBlock *parent){
    this->myParent = parent;
    this->setCursor(Qt::OpenHandCursor);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->setAcceptDrops(true);
    this->id = this->getNextId();

    // vytvoreni datoveho typu portu
    int typeId = QMetaType::type(dataTypeName.toUtf8().constData());
    if (typeId != QMetaType::UnknownType) {
        void *myClassPtr = QMetaType::create(typeId);
        this->dataType = static_cast<AbstractType *>(myClassPtr);
    }
    this->dataType->setMyParent(this);
}

QRectF Port::boundingRect() const { return QRectF(0, 0, 2 * this->PORT_RADIUS, 2 * this->PORT_RADIUS); }

void Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    // prostor pro port
    QRectF portBox = boundingRect();

    // nastaveni barvy portu
    QBrush brush(this->WIRELESS_UNSET_IN_PORT_COLOR);

    (this->inPort) ? brush.setColor(this->WIRELESS_UNSET_IN_PORT_COLOR) : brush.setColor(this->WIRELESS_OUT_PORT_COLOR);

    if (this->dataType->getValuesSet()) { brush.setColor(this->WIRELESS_SET_IN_PORT_COLOR); }

    if (this->portWire != nullptr) { brush.setColor(this->WIRED_IN_OUT_PORT_COLOR); }

    if (this->onMouse || this->dragOver) { brush.setColor(this->HOVER_IN_OUT_PORT_COLOR); }

    // vykresleni portu
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(portBox);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Port::setPortID(int value) { this->id = value; }

int Port::getPortID() {return this->id;}

int Port::getPortRadius() { return this->PORT_RADIUS; }

void Port::setInPort(bool value) { this->inPort = value; }

bool Port::getInPort() { return this->inPort; }

Wire *Port::getWire() { return this->portWire; }

void Port::setWire(Wire *value) { this->portWire = value; }

AbstractType *Port::getDataType() { return this->dataType; }

QString Port::createToolTip() {
    QString toolTip = "";
    toolTip += this->getDataType()->getValueName(0);
    toolTip += ": ";
    toolTip += QString::number(this->getDataType()->getValue(0));
    for (int i = 1; i < this->getDataType()->getValuesLength(); i++) {
        toolTip += "\n";
        toolTip += this->getDataType()->getValueName(i);
        toolTip += ": ";
        toolTip += QString::number(this->getDataType()->getValue(i));
    }
    return toolTip;
}

void Port::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    this->onMouse = true;
    this->update();
    this->setToolTip(this->createToolTip());
    Q_UNUSED(event);
}

void Port::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    this->onMouse = false;
    this->update();
    setCursor(Qt::OpenHandCursor);
    Q_UNUSED(event);
}

void Port::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::RightButton){
        if(this->portWire != nullptr){
            QMessageBox::warning(0, "Error", "Port is connected!");
        } else {
            FillValuesPort fillValuesPort(this);
            fillValuesPort.setModal(true);
            fillValuesPort.exec();
        }
    } else {
        setCursor(Qt::ClosedHandCursor);
    }
}

void Port::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(Qt::OpenHandCursor);
    this->update();
    Q_UNUSED(event);
}

void Port::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if ((qobject_cast<MainWindow *>(this->myParent->myParent->parent()))->getWireEnabled()) {


    // pro zabraneni nechtenych dragu pri kliknuti
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance()) { return; }

    // promenne pro drag
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    // kdyz v portu je drat, tak se znici
    if (this->portWire != nullptr) {
        this->portWire->getOtherPort(this)->portWire = nullptr;
        delete this->portWire;
        this->portWire = nullptr;
    }

    // vytvoreni dratu
    this->portWire = new Wire(myParent->myParent);

    // pokud se taha z in-portu, tak se mu tento port da na startPort jinak na endPort
    (this->inPort) ? this->portWire->setStartPort(this) : this->portWire->setEndPort(this);

    // pridani dratu na scenu
    this->myParent->myParent->addItem(this->portWire);

    // zapoceti dragu
    drag->exec();

    // kdyz se portWire po dragu nerovna null
    if (this->portWire != nullptr) {

        // tak se zkontroluje zdali vede z portu do portu - kdyz ne, tak se znici
        if (this->portWire->getStartPort() == nullptr || this->portWire->getEndPort() == nullptr) {

            // kdyz ma pouze startPort, tak se nastavi danemu portu, ze do neho nevede drat
            if (this->portWire->getStartPort() != nullptr) {
                this->portWire->getStartPort()->portWire = nullptr;

            // kdyz ma pouze endPort, tak se nastavi danemu portu, ze do neho nevede drat
            } else if (this->portWire->getEndPort() != nullptr) {
                this->portWire->getEndPort()->portWire = nullptr;
            }

            // porom se drat znici
            delete this->myParent->myParent->items().first();
        }
    }
    }
}

void Port::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = true;
    this->update();
    Q_UNUSED(event);
}

void Port::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = false;
    this->update();
    Q_UNUSED(event);
}

void Port::dropEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = false;

    // kdyz tahneme drat na port, ktery uz ma drat, tak drat znicime
    if (this->portWire != nullptr) {

        // ukazatl na tazeny drat
        Wire *tempWire = qgraphicsitem_cast<Wire *>(this->myParent->myParent->items().first());

        // nastaveni portu, z ktereho drat vede, ze z neho zadny drat nevede
        if (tempWire->getEndPort() != nullptr) {
            tempWire->getEndPort()->portWire = nullptr;
        } else if (tempWire->getStartPort() != nullptr) {
            tempWire->getStartPort()->portWire = nullptr;
        }

        // zniceni dratu
        delete this->myParent->myParent->items().first();

    // jinak portu nastavime tento drat a zkontrolujeme jestli neporusuje nejaka pravidla
    } else {        

        // nastaveni dratu portu
        this->portWire = qgraphicsitem_cast<Wire *>(this->myParent->myParent->items().first());

        // kdyz se drat dotahl na in-port
        if (this->inPort) {

            if (this->portWire->getEndPort() == nullptr) {
                this->portWire->getStartPort()->portWire = nullptr;
                delete this->myParent->myParent->items().first();
                this->portWire = nullptr;

            } else {

                if (this->dataType->getType() != this->portWire->getEndPort()->getDataType()->getType()) {
                    this->portWire->getEndPort()->portWire = nullptr;
                    delete myParent->myParent->items().first();
                    this->portWire = nullptr;
                } else {
                    // kdyz je startPort dratu uz zabrany, tak drat znicime
                    if (this->portWire->getStartPort() != nullptr) {
                        this->portWire->getStartPort()->portWire = nullptr;
                        delete this->myParent->myParent->items().first();
                        this->portWire = nullptr;

                    // jinak...
                    } else {

                        // kdyz endPort dratu patri stejnemu bloku, tak drat znicime
                        if (this->portWire->getEndPort()->myParent == this->myParent) {
                            this->portWire->getEndPort()->portWire = nullptr;
                            delete myParent->myParent->items().first();
                            this->portWire = nullptr;

                        // jinak dratu nastavime tento port jako startPort
                        } else {
                            this->portWire->setStartPort(this);
                            this->portWire->setDragFinished(true);
                            this->portWire->update();
                        }
                    }
                }
            }

        // kdyz se dotahl na out-port
        } else {
            if (this->portWire->getStartPort() == nullptr) {
                this->portWire->getEndPort()->portWire = nullptr;
                delete myParent->myParent->items().first();
                this->portWire = nullptr;

            } else {

                if (this->dataType->getType() != this->portWire->getStartPort()->getDataType()->getType()) {
                    this->portWire->getStartPort()->portWire = nullptr;
                    delete this->myParent->myParent->items().first();
                    this->portWire = nullptr;
                } else {

                    // kdyz je endPort dratu uz zabrany, tak drat znicime
                    if (this->portWire->getEndPort() != nullptr) {
                        this->portWire->getEndPort()->portWire = nullptr;
                        delete myParent->myParent->items().first();
                        this->portWire = nullptr;

                    // jinak...
                    } else {

                        // kdyz startPort dratu patri stejnemu bloku, tak drat znicime
                        if (this->portWire->getStartPort()->myParent == this->myParent) {
                            this->portWire->getStartPort()->portWire = nullptr;
                            delete this->myParent->myParent->items().first();
                            this->portWire = nullptr;

                        // jinak dratu nastavime tento port jako endPort
                        } else {
                            this->portWire->setEndPort(this);
                            this->portWire->setDragFinished(true);
                            this->portWire->update();
                        }
                    }
                }
            }
        }
    }

    setCursor(Qt::OpenHandCursor);
    this->setAcceptHoverEvents(true);
    this->update();

    Q_UNUSED(event);
}

int Port::countBlocks() {
   int count = 0;
   QGraphicsItemGroup *previous = nullptr;
   QGraphicsItemGroup *actual = nullptr;
   for (int i = 0; i < this->myParent->myParent->items().length(); i++) {
       actual = this->myParent->myParent->items().at(i)->group();
       if (actual != nullptr && actual != previous) { count++; }
       previous = actual;
   }
   return count;
}

AbstractBlock *Port::getBlock(int index) {
    int count = 0;
    QGraphicsItemGroup *previous = nullptr;
    QGraphicsItemGroup *actual = nullptr;
    for (int i = 0; i < this->myParent->myParent->items().length(); i++) {
        actual = this->myParent->myParent->items().at(i)->group();
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

int Port::getNextId(bool value) {
    static int portId = 0;
    if (value) {
        for (int i = 0; i < this->countBlocks(); i++) {
            AbstractBlock *block = this->getBlock(i);
            for (int j = 0; j < block->getInPortsCount(); j++) {
                if (portId < block->getInPort(j)->getPortID()) {
                    portId = block->getInPort(j)->getPortID();
                }
            }
            for (int j = 0; j < block->getOutPortsCount(); j++) {
                if (portId < block->getOutPort(j)->getPortID()) {
                    portId = block->getOutPort(j)->getPortID();
                }
            }
        }
    }
    portId++;
    return portId;
}

bool Port::getIsInCycle() { return this->isInCycle; }

void Port::setIsInCycle(bool value) { this->isInCycle = value; }
