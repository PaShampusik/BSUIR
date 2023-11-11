#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QCursor>
#include <QtMath>

class Triangle: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Triangle(short x1 = 10, short y1 = 20, short x2 = 20, short y2 = 10,
             short x3 = 30, short y3 = 30, QObject *parent = nullptr) : QObject (parent) {

        this->x1 = x1; this->y1 = y1;
        this->x2 = x2; this->y2 = y2;
        this->x3 = x3; this->y3 = y3;

        size = 1; degree = 0;

        r = rand()%255;
        g = rand()%255;
        b = rand()%255;

        AB = sqrt(pow((x1 - x2), 2)+pow((y1 - y2), 2));
        BC = sqrt(pow((x2 - x3), 2)+pow((y2 - y3), 2));
        AC = sqrt(pow((x1 - x3), 2)+pow((y1 - y3), 2));

        DefaultSize = AB > BC ? AB : BC;
        DefaultSize = DefaultSize > AC? DefaultSize : AC;
    }

private:
    short x1, y1, x2, y2, x3, y3;
    double size, degree;

    double DefaultSize;
    double AB, BC, AC;

    short r, g, b;

public:

    QRectF boundingRect() const {
        return QRectF(-DefaultSize*20, -DefaultSize*20, DefaultSize*40, DefaultSize*40);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

    QString Parametrs ();
};

#endif // TRIANGLE_H
