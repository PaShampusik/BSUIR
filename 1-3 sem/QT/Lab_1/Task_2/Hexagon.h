#ifndef HEXAGON_H
#define HEXAGON_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QCursor>
#include <QtMath>



class Hexagon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Hexagon(QObject *parent = nullptr) : QObject (parent),
        degree(0), size(1), r(rand()%255), g(rand()%255), b(rand()%255) {}
  ~Hexagon() {}



private:
    double degree, size;
    short r, g, b;
    double DefaultSize = 110;

    QRectF boundingRect() const {
        return QRectF(-DefaultSize*20, -DefaultSize*20, DefaultSize*400, DefaultSize*400);
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

#endif // HEXAGON_H
