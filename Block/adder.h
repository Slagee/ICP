#ifndef ADDER_H
#define ADDER_H

#include "abstractblock.h"

class adder : public abstractblock {
private:
    const int BLOCK_WIDTH = 100;
    const int BLOCK_HEIGHT = 40;
    const QString BLOCK_NAME = "ADDER";

public:
    adder(qreal x, qreal y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // ADDER_H
