#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QCursor>
#include <QKeyEvent>



class Rectangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
   // Q_INTERFACES(QObject, QGraphicsItem)
public:
     Rectangle(short width = 300, short height = 200,
        short r = rand() % 255, short g = rand() % 255, short b = rand() % 255,
        QObject* parent = nullptr) : QObject(parent) {
        this->width = 300; this->height = 200;
        this->r = r; this->g = g; this->b = b;
        DefaultSize = width > height ? width : height;
    }
    ~Rectangle()
    { 
      
    }

    //void paintEvent(QPaintEvent* event, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    /*QPainter* painter;*/
    short width = 300, height = 200;
    double DefaultSize;
    short r, g, b;

    QRectF boundingRect() const {
        return QRectF(-DefaultSize - 2000, -DefaultSize - 2000, DefaultSize * 2 + 4500, DefaultSize * 2 + 4500);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public:

    //virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
};

#endif  RECTANGLE_H
