#ifndef TELEGA_H
#define TELEGA_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <cmath>



class Telega : public QGraphicsItem {
public:
    Telega(int width_ = 500, int height_ = 200) {
        width = width_;
        height = height_;

        R = height/2;
        r = R / 5;

        rotationAngle = 0;
    }
    ~Telega() {};

protected:
    int width, height;
    double R, r, rotationAngle;

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TELEGA_H
