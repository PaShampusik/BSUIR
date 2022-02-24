#include "wheels.h"

Wheels::Wheels() {};

Wheels::~Wheels() {}

       QRectF Wheels::boundingRect() const {
        return QRectF(-100, -100, 700, 1000);
    }

    void Wheels::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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

        painter->setBrush(QBrush(Qt::blue));

        painter->translate(height - R, height + R);

        painter->drawEllipse(QRectF(-R, -R, R, R));

        painter->translate(width - R, 0);

        painter->drawEllipse(QRectF(-R, -R, R, R));


        painter->setBrush(QColor(Qt::white));

//правый:

        painter->rotate(0);

        painter->translate(-R + r * 2.1, -2*r - 8);

        painter->rotate(rotationAngle);

        painter->drawEllipse(QRectF(-r, -r, r, r));

//левый:

        painter->rotate(-rotationAngle);

        painter->translate(-width + R, 0);

        painter->rotate(rotationAngle);

        painter->drawEllipse(QRectF(-r, -r, r, r));

        rotationAngle += 0.5 + k;
    }

    void Wheels::speedup(){
        k += 0.7;
    }

