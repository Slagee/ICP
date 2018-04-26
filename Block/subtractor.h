#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H

#include "abstractblock.h"

class subtractor : public abstractblock {
private:
    const int BLOCK_WIDTH = 120;
    const int BLOCK_HEIGHT = 50;
    const QString BLOCK_NAME = "SUBTRACTOR";

public:
    subtractor(qreal x, qreal y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);
};

#endif // SUBTRACTOR_H
