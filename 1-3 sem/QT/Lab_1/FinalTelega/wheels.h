#ifndef WHEELS_H
#define WHEELS_H

#include "telega.h"

class Wheels : public Telega {
public:
    Wheels();
    ~Wheels();
    void speedup();
protected:

    double k = 0;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // WHEELS_H
