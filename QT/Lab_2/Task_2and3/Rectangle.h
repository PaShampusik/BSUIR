#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>

#include "Shared_Ptr.h"





class Rectangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
        // Q_INTERFACES(QObject, QGraphicsItem)
public:
    Rectangle(
        QObject* parent = nullptr) : QObject(parent) {
        this->width = 150; this->height = 75;
        this->r = r; this->g = g; this->b = b;
    }
    ~Rectangle()
    {

    }

    Weak_Ptr<Rectangle> loop;

protected:
    short width = 150, height = 75;
    short r = 120, g = 120, b = 120;
   // Weak_Ptr<Rectangle> loop;

    QRectF boundingRect() const {
        return QRectF(-2000, -2000, 4500, 4500);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public:

    //virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
};

#endif  RECTANGLE_H

