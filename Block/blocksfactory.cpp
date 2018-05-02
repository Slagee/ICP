#include "blocksfactory.h"

void blocksfactory(int classId, int x, int y, QGraphicsScene *parent) {
    switch (classId) {
    case(0):
        parent->addItem(new adder(x, y, parent));
        break;
    case(1):
        parent->addItem(new subtractor(x, y, parent));
        break;
    case(2):
        parent->addItem(new multiplier(x, y, parent));
        break;
    case(3):
        parent->addItem(new divider(x, y, parent));
        break;
    case(4):
        parent->addItem(new adder1w1a2w1to1w1a2w2a3w3(x, y, parent));
        break;
    case(5):
        parent->addItem(new adder1w1a2w2a3w3to1w1a2w1(x, y, parent));
        break;
    }
}


