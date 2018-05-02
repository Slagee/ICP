#ifndef BLOCKSFACTORY_H
#define BLOCKSFACTORY_H

#include <QString>
#include <QGraphicsScene>

class adder;
class subtractor;
class multiplier;
class divider;
class adder1w1a2w1to1w1a2w2a3w3;
class adder1w1a2w2a3w3to1w1a2w1;

#include "Block/adder.h"
#include "Block/subtractor.h"
#include "Block/multiplier.h"
#include "Block/divider.h"
#include "Block/adder1w1a2w1to1w1a2w2a3w3.h"
#include "Block/adder1w1a2w2a3w3to1w1a2w1.h"

const int NUMBER_OF_BLOCKS = 6;
const QString BLOCKS_CLASSES[NUMBER_OF_BLOCKS] = {"adder", "subtractor", "multiplier", "divider", "adder1w1a2w1to1w1a2w2a3w3", "adder1w1a2w2a3w3to1w1a2w1"};


void blocksfactory(int classId, int x, int y, QGraphicsScene *parent = 0);

#endif // BLOCKSFACTORY_H
