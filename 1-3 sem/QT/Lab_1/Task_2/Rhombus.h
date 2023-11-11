#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "rectangle.h"
#include "Square.h"

class Rhombus : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    Rhombus(short length = 150,
                       double RotationAngle = 0,
                       short r = rand()%255, short g = rand()%255, short b = rand()%255,
                       QObject *parent = nullptr) : QObject (parent) {
        size = 1;

        this->length = length;
        degree = RotationAngle;

        this->r = r; this->g = g; this->b = b;

        DefaultSize = length;
    }
    ~Rhombus()
    {
    };
protected:

    short length;
    double size;
    double DefaultSize;
    double degree;
    short r, g, b;

    QRectF boundingRect() const {
        return QRectF(-DefaultSize-2000, -DefaultSize-2000, DefaultSize*2+4500, DefaultSize*2+4500);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    public:

    virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

    QString Parametrs ();
};

#endif // RHOMBUS_H

