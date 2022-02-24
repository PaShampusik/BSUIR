#include "telega.h"

QRectF Telega::boundingRect() const {
    return QRectF(-100, -100, 700, 800);
}

 void Telega::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option); Q_UNUSED(widget);


    painter->setBrush(QBrush(Qt::yellow));

    painter->drawRect(0, 0, width, height);

    painter->setBrush(QBrush(Qt::blue));

    painter->drawRect(0, 0, 500, 100);

    painter->setBrush(QBrush(Qt::black));

    painter->drawRect(30, -50, 200, 50);//рисуем груз

    QPolygon pol;

    pol << QPoint(250, 0) << QPoint(370, -70) << QPoint(470, 0);

    painter->drawPolygon(pol);
}
