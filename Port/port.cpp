#include "port.h"

port::port(abstractBlock *parent){
    this->myParent = parent;
    this->dataType = new oneDecimalNumber(this);
    this->setCursor(Qt::OpenHandCursor);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->setAcceptDrops(true);
}

QRectF port::boundingRect() const { return QRectF(0, 0, 2 * this->PORT_RADIUS, 2 * this->PORT_RADIUS); }

void port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // prostor pro port
    QRectF portBox = boundingRect();

    // pro nastaveni barvy portu
    QBrush brush(this->WIRELESS_UNSET_IN_PORT_COLOR);

    (this->inPort) ? brush.setColor(this->WIRELESS_UNSET_IN_PORT_COLOR) : brush.setColor(this->WIRELESS_OUT_PORT_COLOR);

    if (this->portWire != nullptr) { brush.setColor(this->WIRED_IN_OUT_PORT_COLOR); }

    if (this->onMouse || this->dragOver) { brush.setColor(this->HOVER_IN_OUT_PORT_COLOR); }

    // vykresleni portu
    painter->setBrush(brush);
    painter->drawEllipse(portBox);
}

int port::getPortRadius() { return this->PORT_RADIUS; }

void port::setInPort(bool value) { this->inPort = value; }

bool port::getInPort() { return this->inPort; }

void port::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    this->onMouse = true;
    this->update();
    QGraphicsItem::hoverEnterEvent(event);
}

void port::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    this->onMouse = false;
    this->update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void port::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(Qt::ClosedHandCursor);
    Q_UNUSED(event);
}

void port::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(Qt::OpenHandCursor);
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void port::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    // pro zabraneni nechtenych dragu pri kliknuti
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance()) { return; }

    // promenne pro drag
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    // vytvoreni dratu
    this->portWire = new wire(myParent->myParent);

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

void port::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = true;
    this->update();
    Q_UNUSED(event);
}

void port::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = false;
    this->update();
    Q_UNUSED(event);
}

void port::dropEvent(QGraphicsSceneDragDropEvent *event) {
    this->dragOver = false;

    // kdyz tahneme drat na port, ktery uz ma drat, tak drat znicime
    if (this->portWire != nullptr) {

        // ukazatl na tazeny drat
        wire *tempWire = qgraphicsitem_cast<wire *>(this->myParent->myParent->items().first());

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
        this->portWire = qgraphicsitem_cast<wire *>(this->myParent->myParent->items().first());

        // kdyz se drat dotahl na in-port
        if (this->inPort) {

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

        // kdyz se dotahl na out-port
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

    this->update();
    Q_UNUSED(event);
}
