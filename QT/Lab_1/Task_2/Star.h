#ifndef STAR_H
#define STAR_H

#include <QGraphicsItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

class Star : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Star(int VerticlesAmount = 5, int R = 100, int r = 50, QObject *parent = nullptr) :
        QObject(parent), QGraphicsItem ()
    {
        this->R = R;
        this->r = r;
        this->VerticlesAmount = VerticlesAmount;

        DefaultSize = R > r ? R : r;
        x = DefaultSize/2;
        y = DefaultSize/2;
        degree = 0;
        size = 1;
        p_x = new double[VerticlesAmount * 2+1];
        p_y = new double[VerticlesAmount * 2+1];
    }

    ~Star() {
        delete p_x;
        delete p_y;
    }

private:

    virtual QRectF boundingRect() const {

        return QRectF(-DefaultSize-2000, -DefaultSize-2000, DefaultSize + 4500, DefaultSize + 4500);
    }

public:

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;
    virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QString Parametrs();

    int R, r, VerticlesAmount;
    double degree;
    double DefaultSize, size;
    double *p_x, *p_y;
    double x, y;
};

#endif // STAR_H
