#include "BlocksFactory.h"

void blocksFactory(int classId, int x, int y, QGraphicsScene *parent) {
    switch (classId) {
    case(0):
        parent->addItem(new Adder(x, y, parent));
        break;
    case(1):
        parent->addItem(new Subtractor(x, y, parent));
        break;
    case(2):
        parent->addItem(new Multiplier(x, y, parent));
        break;
    case(3):
        parent->addItem(new Divider(x, y, parent));
        break;
    case(4):
        parent->addItem(new Adder1w1a2w1to1w1a2w2a3w3(x, y, parent));
        break;
    case(5):
        parent->addItem(new Adder1w1a2w2a3w3to1w1a2w1(x, y, parent));
        break;
    case(6):
        parent->addItem(new Adder1w2to1w1(x, y, parent));
        break;
    case(7):
        parent->addItem(new Adder1w3to1w1a2w1(x, y, parent));
        break;
    case(8):
        parent->addItem(new Round(x, y, parent));
        break;
    case(9):
        parent->addItem(new WaterLaboratory(x, y, parent));
        break;
    }
}


